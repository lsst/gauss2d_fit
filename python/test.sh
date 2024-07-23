#!/bin/sh

export DYLD_LIBRARY_PATH=${LD_LIBRARY_PATH}
pytest "$@"
