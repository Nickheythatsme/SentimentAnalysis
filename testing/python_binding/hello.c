
static PyMethodDef HelloMethods[] = {
    { "hello", hello_wrapper, METH_VARARGS, "Say hello" },
    { NULL, NULL, 0, NULL }
};

DL_EXPORT(void) inithello(void)
{
    Py_InitModule("hello", HelloMethods);
}

char * hello(char * what)
{
    char *ret = (char*) malloc(strlen(what) + strlen("hello ") + 1);
    int i;
    for(i = 0; i < strlen("hello ") + strlen(what); ++i)
    {
        ret[i] = 'a';
    }
    ret[i] = '\0';
    return ret;
}

static PyObject * hello_wrapper(PyObject * self, PyObject * args)
{
  char * input;
  char * result;
  PyObject * ret;

  // parse arguments
  if (!PyArg_ParseTuple(args, "s", &input)) {
    return NULL;
  }

  // run the actual function
  result = hello(input);

  // build the resulting string into a Python object.
  ret = PyString_FromString(result);
  free(result);

  return ret;
}
