/** 
 *  PyVortex: Vortex Library Python bindings
 *  Copyright (C) 2009 Advanced Software Production Line, S.L.
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public License
 *  as published by the Free Software Foundation; either version 2.1
 *  of the License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this program; if not, write to the Free
 *  Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 *  02111-1307 USA
 *  
 *  You may find a copy of the license under this software is released
 *  at COPYING file. This is LGPL software: you are welcome to develop
 *  proprietary applications using this library without any royalty or
 *  fee but returning back any change, improvement or addition in the
 *  form of source code, project image, documentation patches, etc.
 *
 *  For commercial support on build BEEP enabled solutions contact us:
 *          
 *      Postal address:
 *         Advanced Software Production Line, S.L.
 *         C/ Antonio Suarez Nº 10, 
 *         Edificio Alius A, Despacho 102
 *         Alcalá de Henares 28802 (Madrid)
 *         Spain
 *
 *      Email address:
 *         info@aspl.es - http://www.aspl.es/vortex
 */

#include <py_vortex_connection.h>

struct _PyVortexConnection {
	/* header required to initialize python required bits for
	   every python object */
	PyObject_HEAD

	/* pointer to the VortexConnection object */
	VortexConnection * conn;

	/** 
	 * @internal variable used to signal the type to close the
	 * connection wrapped (VortexConnection) when the reference
	 * PyVortexConnection is garbage collected.
	 */
	axl_bool           close_ref;

	/** 
	 * @brief Reference to the PyVortexCtx that was used to create
	 * the connection. In may be null because some function inside
	 * the PyVortex API may create a connection
	 * (PyVortexConnection) reusing a VortexConnection
	 * reference. See \ref py_vortex_connection_create.
	 */ 
	PyObject       * py_vortex_ctx;
};

#define PY_VORTEX_CONNECTION_CHECK_NOT_ROLE(py_conn, role, method)                                                \
do {                                                                                                              \
	if (vortex_connection_get_role (((PyVortexConnection *)py_conn)->conn) == role) {                         \
	         py_vortex_log (PY_VORTEX_CRITICAL,                                                               \
                                "trying to run a method %s not supported by the role %d, connection id: %d",      \
				method, role, vortex_connection_get_id (((PyVortexConnection *)py_conn)->conn));  \
	         Py_INCREF(Py_None);                                                                              \
		 return Py_None;                                                                                  \
	}                                                                                                         \
} while(0);
		 

/** 
 * @brief Allows to get the VortexConnection reference inside the
 * PyVortexConnection.
 *
 * @param py_conn The reference that holds the connection inside.
 *
 * @return A reference to the VortexConnection inside or NULL if it fails.
 */
VortexConnection * py_vortex_connection_get  (PyVortexConnection * py_conn)
{
	/* return NULL reference */
	if (py_conn == NULL)
		return NULL;
	/* return py connection */
	return py_conn->conn;
}

static int py_vortex_connection_init_type (PyVortexConnection *self, PyObject *args, PyObject *kwds)
{
    return 0;
}

/** 
 * @brief Function used to allocate memory required by the object vortex.Connection
 */
static PyObject * py_vortex_connection_new (PyTypeObject *type, PyObject *args, PyObject *kwds)
{
	PyVortexConnection * self;
	const char         * host = NULL;
	const char         * port = NULL;
	PyObject           * py_vortex_ctx = NULL;

	/* create the object */
	self = (PyVortexConnection *)type->tp_alloc(type, 0);

	/* now parse arguments */
	static char *kwlist[] = {"ctx", "host", "port", NULL};

	/* check args */
	if (args != NULL) {
		/* parse and check result */
		if (! PyArg_ParseTupleAndKeywords(args, kwds, "|Oss", kwlist, &py_vortex_ctx, &host, &port)) 
			return NULL;

		/* check for empty creation */
		if (py_vortex_ctx == NULL) {
			py_vortex_log (PY_VORTEX_DEBUG, "found empty request to create a PyVortexConnection ref..");
			return (PyObject *) self;
		}
			
		
		/* create the vortex connection in a blocking manner */
		self->conn = vortex_connection_new (py_vortex_ctx_get (py_vortex_ctx), host, port, NULL, NULL);

		/* own a copy of py_vortex_ctx */
		self->py_vortex_ctx = py_vortex_ctx;
		Py_INCREF (__PY_OBJECT (py_vortex_ctx) );

		/* signal this instance as a master copy to be closed
		 * if the reference is collected and the connection is
		 * working */
		self->close_ref = axl_true;

		if (vortex_connection_is_ok (self->conn, axl_false)) {
			py_vortex_log (PY_VORTEX_DEBUG, "created connection id %d, with %s:%s",
				       vortex_connection_get_id (self->conn), 
				       vortex_connection_get_host (self->conn),
				       vortex_connection_get_port (self->conn));
		} else {
			py_vortex_log (PY_VORTEX_CRITICAL, "failed to connect with %s:%s, connection id: %d",
				       vortex_connection_get_host (self->conn),
				       vortex_connection_get_port (self->conn),
				       vortex_connection_get_id (self->conn));
		} /* end if */
	} /* end if */

	return (PyObject *)self;
}

/** 
 * @brief Function used to finish and dealloc memory used by the object vortex.Connection
 */
static void py_vortex_connection_dealloc (PyVortexConnection* self)
{
	int conn_id = vortex_connection_get_id (self->conn);

	py_vortex_log (PY_VORTEX_DEBUG, "finishing PyVortexConnection id: %d (%p)", conn_id, self);

	/* finish the connection in the case it is no longer referenced */
	if (vortex_connection_is_ok (self->conn, axl_false) && self->close_ref) {
		py_vortex_log (PY_VORTEX_DEBUG, "shutting down BEEP session associated at connection finalize id: %d (connection is ok, and close_ref is activated)", 
			       vortex_connection_get_id (self->conn));
		vortex_connection_shutdown (self->conn);
		vortex_connection_close (self->conn);
	} else {
		py_vortex_log (PY_VORTEX_DEBUG, "unref the connection id: %d", vortex_connection_get_id (self->conn));
		/* only unref the connection */
		vortex_connection_unref (self->conn, "py_vortex_connection_dealloc");
	} /* end if */

	/* nullify */
	self->conn = NULL;

	/* decrease reference on PyVortexCtx used */
	if (self->py_vortex_ctx) {
		py_vortex_log (PY_VORTEX_DEBUG, "unref PyVortexCtx associated: %p", self->py_vortex_ctx);
		Py_DECREF (__PY_OBJECT (self->py_vortex_ctx));
		self->py_vortex_ctx = NULL;
	} /* endif */

	/* free the node it self */
	self->ob_type->tp_free ((PyObject*)self);

	py_vortex_log (PY_VORTEX_DEBUG, "terminated PyVortexConnection dealloc with id: %d (self: %p)", conn_id, self);

	return;
}

/** 
 * @brief Direct wrapper for the vortex_connection_is_ok function. 
 */
static PyObject * py_vortex_connection_is_ok (PyVortexConnection* self)
{
	PyObject *_result;

	/* call to check connection and build the value with the
	   result. Do not free the connection in the case of
	   failure. */
	_result = Py_BuildValue ("i", vortex_connection_is_ok (self->conn, axl_false));
	
	return _result;
}

static PyObject * py_vortex_connection_pop_channel_error (PyVortexConnection * self)
{
	/* create a tuple to contain arguments */
	PyObject * result;
	int        code = 0;
	char     * msg  = NULL;

	/* check if this is a listener connection that cannot provide
	   this service */
	PY_VORTEX_CONNECTION_CHECK_NOT_ROLE(self, VortexRoleMasterListener, "pop_channel_error");

	/* check for channel errors */
	if (vortex_connection_pop_channel_error (self->conn, &code, &msg)) {
		/* found error message */
		result = PyTuple_New (2);
		PyTuple_SetItem (result, 0, Py_BuildValue ("i", code));
		PyTuple_SetItem (result, 1, Py_BuildValue ("s", msg));

		py_vortex_log (PY_VORTEX_DEBUG, "poping channel error code: %d, msg: %s",
			       code, msg);
		
		/* release msg */
		axl_free (msg);

		/* return tuple */
		return result;
	} /* end if */

	/* no error is found, return None */
	Py_INCREF (Py_None);
	return Py_None;
}

/** 
 * @internal function that maps connection roles to string values.
 */
const char * __py_vortex_connection_stringify_role (VortexConnection * conn)
{
	/* check known roles to return its appropriate string */
	switch (vortex_connection_get_role (conn)) {
	case VortexRoleInitiator:
		return "initiator";
	case VortexRoleListener:
		return "listener";
	case VortexRoleMasterListener:
		return "master-listener";
	default:
		break;
	}

	/* return unknown string */
	return "unknown";
}

/** 
 * @brief Direct wrapper for the vortex_connection_close function. 
 */
static PyObject * py_vortex_connection_close (PyVortexConnection* self)
{
	PyObject *_result;
	axl_bool  result;

	if (self->conn) {
		py_vortex_log (PY_VORTEX_DEBUG, "closing connection id: %d (%s)",
			       vortex_connection_get_id (self->conn), __py_vortex_connection_stringify_role (self->conn));
	} /* end if */

	/* call to check connection and build the value with the
	   result. Do not free the connection in the case of
	   failure. */
	result  = vortex_connection_close (self->conn);
	_result = Py_BuildValue ("i", result);

	/* check to nullify connection reference in the case the connection is closed */
	if (result) {
		self->conn = NULL; 
	}
	
	return _result;
}

/** 
 * @brief Direct wrapper for the vortex_connection_shutdown function. 
 */
PyObject * py_vortex_connection_shutdown (PyVortexConnection* self)
{
	py_vortex_log (PY_VORTEX_DEBUG, "calling to shutdown connection id: %d, self: %p",
		       vortex_connection_get_id (self->conn), self);

	/* shut down the connection */
	vortex_connection_shutdown (self->conn);

	/* return none */
	Py_INCREF (Py_None);
	return Py_None;
}

/** 
 * @brief Direct wrapper for the vortex_connection_status function. 
 */
PyObject * py_vortex_connection_status (PyVortexConnection* self)
{
	PyObject *_result;

	/* call to check connection and build the value with the
	   result. Do not free the connection in the case of
	   failure. */
	_result = Py_BuildValue ("i", vortex_connection_get_status (self->conn));
	
	return _result;
}

/** 
 * @brief Direct wrapper for the vortex_connection_get_message function. 
 */
PyObject * py_vortex_connection_error_msg (PyVortexConnection* self)
{
	PyObject *_result;
	/* printf ("Received request to return status message: %s\n", vortex_connection_get_message (self->conn)); */

	/* call to check connection and build the value with the
	   result. Do not free the connection in the case of
	   failure. */
	_result = Py_BuildValue ("z", vortex_connection_get_message (self->conn));
	
	return _result;
}

/** 
 * @brief This function implements the generic attribute getting that
 * allows to perform complex member resolution (not merely direct
 * member access).
 */
PyObject * py_vortex_connection_get_attr (PyObject *o, PyObject *attr_name) {
	const char         * attr = NULL;
	PyObject           * result;
	PyVortexConnection * self = (PyVortexConnection *) o;

	/* now implement other attributes */
	if (! PyArg_Parse (attr_name, "s", &attr))
		return NULL;

	/* printf ("received request to return attribute value of '%s'..\n", attr); */

	if (axl_cmp (attr, "error_msg")) {
		/* found error_msg attribute */
		return Py_BuildValue ("s", vortex_connection_get_message (self->conn));
	} else if (axl_cmp (attr, "status")) {
		/* found status attribute */
		return Py_BuildValue ("i", vortex_connection_get_status (self->conn));
	} else if (axl_cmp (attr, "host")) {
		/* found host attribute */
		return Py_BuildValue ("s", vortex_connection_get_host (self->conn));
	} else if (axl_cmp (attr, "port")) {
		/* found port attribute */
		return Py_BuildValue ("s", vortex_connection_get_port (self->conn));
	} else if (axl_cmp (attr, "num_channels")) {
		/* found num_channels attribute */
		return Py_BuildValue ("i", vortex_connection_channels_count (self->conn));
	} else if (axl_cmp (attr, "role")) {
		/* found role attribute */
		switch (vortex_connection_get_role (self->conn)) {
		case VortexRoleInitiator:
			return Py_BuildValue ("s", "initiator");
		case VortexRoleListener:
			return Py_BuildValue ("s", "listener");
		case VortexRoleMasterListener:
			return Py_BuildValue ("s", "master-listener");
		default:
			break;
		}
		return Py_BuildValue ("s", "unknown");
	} /* end if */

	/* printf ("Attribute not found: '%s'..\n", attr); */

	/* first implement generic attr already defined */
	result = PyObject_GenericGetAttr (o, attr_name);
	if (result)
		return result;
	
	return NULL;
}


static PyObject * py_vortex_connection_open_channel (PyObject * self, PyObject * args, PyObject * kwds)
{
	PyObject           * py_channel;
	VortexChannel      * channel;
	int                  number;
	const char         * profile;
	PyObject           * frame_received      = NULL;
	PyObject           * frame_received_data = NULL;

	/* now parse arguments */
	static char *kwlist[] = {"number", "profile", "frame_received", "frame_received_data", NULL};

	/* check if this is a listener connection that cannot provide
	   this service */
	PY_VORTEX_CONNECTION_CHECK_NOT_ROLE(self, VortexRoleMasterListener, "open_channel");

	/* parse and check result */
	if (! PyArg_ParseTupleAndKeywords(args, kwds, "is|OO", kwlist, &number, &profile, 
					  /* optional parameters */
					  &frame_received, &frame_received_data)) {
		return NULL;
	}

	/* create an empty channel reference */
	py_channel = py_vortex_channel_create_empty (self);

	/* check for frame received configuration */
	if (frame_received && PyCallable_Check (frame_received)) {
		/* call to set the handler */
		if (! py_vortex_channel_configure_frame_received (
			    (PyVortexChannel *) py_channel, 
			    frame_received, 
			    frame_received_data)) {
			
			py_vortex_log (PY_VORTEX_CRITICAL, "failed to configure frame received handler, unable to create channel");

			/* decrease py ref created */
			Py_DECREF (py_channel);
			return NULL;
		}
	} /* end if */

	/* now try to create the channel */
	channel = vortex_channel_new (
		/* pass the BEEP connection */
		PY_CONN_GET(self), 
		/* channel number and profile */
		number, profile,
		/* close handler */
		NULL, NULL, 
		/* frame received handler */
		frame_received ? py_vortex_channel_received : NULL, py_channel,
		/* on channel created */
		NULL, NULL);

	/* check for error found */
	if (channel == NULL) {
		/* release python channel reference */
		Py_DECREF (py_channel);
		Py_INCREF (Py_None);
		return Py_None;
	}

	/* set the channel */
	py_vortex_channel_set ((PyVortexChannel *) py_channel, channel);

	/* return reference created */
	return py_channel;
}

static PyMethodDef py_vortex_connection_methods[] = { 
	/* is_ok */
	{"is_ok", (PyCFunction) py_vortex_connection_is_ok, METH_NOARGS,
	 "Allows to check current vortex.Connection status. In the case False is returned the connection is no longer operative. "},
	/* open_channel */
	{"open_channel", (PyCFunction) py_vortex_connection_open_channel, METH_VARARGS | METH_KEYWORDS,
	 "Allows to open a channel on the provided connection (BEEP session)."},
	/* pop_channel_error */
	{"pop_channel_error", (PyCFunction) py_vortex_connection_pop_channel_error, METH_NOARGS,
	 "API wrapper for vortex_connection_pop_channel_error. Each time this method is called, a tulple (code, msg) is returned containing the error code and the error message. One tuple is returned for each channel error found. In the case no error is stored on the connection None is returned."},
	/* close */
	{"close", (PyCFunction) py_vortex_connection_close, METH_NOARGS,
	 "Allows to close a the BEEP session (vortex.Connection) following all BEEP close negotation phase. The method returns True in the case the connection was cleanly closed, otherwise False is returned. If this operation finishes properly, the reference should not be used."},
	/* shutdown */
	{"shutdown", (PyCFunction) py_vortex_connection_shutdown, METH_NOARGS,
	 "Allows to shutdown the BEEP session. This operation closes the underlaying transport without going into the full BEEP close process. It is still required to call to .close method to fully finish the connection. After the shutdown the caller can still use the reference and check its status. After a close operation the connection cannot be used again."},
 	{NULL}  
}; 


static PyTypeObject PyVortexConnectionType = {
    PyObject_HEAD_INIT(NULL)
    0,                         /* ob_size*/
    "vortex.Connection",       /* tp_name*/
    sizeof(PyVortexConnection),/* tp_basicsize*/
    0,                         /* tp_itemsize*/
    (destructor)py_vortex_connection_dealloc, /* tp_dealloc*/
    0,                         /* tp_print*/
    0,                         /* tp_getattr*/
    0,                         /* tp_setattr*/
    0,                         /* tp_compare*/
    0,                         /* tp_repr*/
    0,                         /* tp_as_number*/
    0,                         /* tp_as_sequence*/
    0,                         /* tp_as_mapping*/
    0,                         /* tp_hash */
    0,                         /* tp_call*/
    0,                         /* tp_str*/
    py_vortex_connection_get_attr, /* tp_getattro*/
    0,                         /* tp_setattro*/
    0,                         /* tp_as_buffer*/
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,  /* tp_flags*/
    "vortex.Connection, the object used to represent a connected BEEP session.",           /* tp_doc */
    0,		               /* tp_traverse */
    0,		               /* tp_clear */
    0,		               /* tp_richcompare */
    0,		               /* tp_weaklistoffset */
    0,		               /* tp_iter */
    0,		               /* tp_iternext */
    py_vortex_connection_methods,     /* tp_methods */
    0, /* py_vortex_connection_members, */ /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)py_vortex_connection_init_type,      /* tp_init */
    0,                         /* tp_alloc */
    py_vortex_connection_new,  /* tp_new */

};

/** 
 * @brief Allows to create a new PyVortexConnection instance using the
 * reference received.
 *
 * @param conn The connection to use as reference to wrap
 *
 * @param acquire_ref Allows to configure if py_conn reference must
 * acquire a reference to the connection.
 *
 * @param close_ref Allows to signal the object created to close or
 * not the connection when the reference is garbage collected.
 *
 * @return A newly created PyVortexConnection reference.
 */
PyObject * py_vortex_connection_create   (VortexConnection * conn, 
					  PyObject         * ctx,
					  axl_bool           acquire_ref,
					  axl_bool           close_ref)
{
	/* return a new instance */
	PyVortexConnection * obj = (PyVortexConnection *) PyObject_CallObject ((PyObject *) &PyVortexConnectionType, NULL); 

	/* check ref created */
	if (obj == NULL) {
		py_vortex_log (PY_VORTEX_CRITICAL, "Failed to create PyVortexConnection object, returning NULL");
		return NULL;
	} /* end if */

	/* configure close_ref */
	obj->close_ref = close_ref;

	/* set channel reference received */
	if (obj && conn) {
		/* check to acquire a ref */
		if (acquire_ref) {
			py_vortex_log (PY_VORTEX_DEBUG, "acquiring a reference to conn: %p, ctx: %p (role: %s)",
				       conn, ctx, __py_vortex_connection_stringify_role (conn));
			/* check ref */
			if (! vortex_connection_ref (conn, "py_vortex_connection_create")) {
				py_vortex_log (PY_VORTEX_CRITICAL, "failed to acquire reference, unable to create connection");
				Py_DECREF (obj);
				return NULL;
			}

			/* configure the ctx received */
			obj->py_vortex_ctx = ctx;
			Py_XINCREF (__PY_OBJECT (obj->py_vortex_ctx));
		} /* end if */

		/* configure the reference */
		obj->conn = conn;
	} /* end if */

	/* return object */
	return (PyObject *) obj;
}

/** 
 * @brief Inits the vortex connection module. It is implemented as a type.
 */
void init_vortex_connection (PyObject * module) 
{
    
	/* register type */
	if (PyType_Ready(&PyVortexConnectionType) < 0)
		return;
	
	Py_INCREF (&PyVortexConnectionType);
	PyModule_AddObject(module, "Connection", (PyObject *)&PyVortexConnectionType);

	return;
}

