#!/usr/bin/env python3

import os
import subprocess
import sys
import tempfile


with tempfile.TemporaryDirectory(prefix="centipede-test-") as test_tmpdir:
    env = os.environ.copy()
    env["TEST_TMPDIR"] = test_tmpdir
    sys.exit(subprocess.run(sys.argv[1:], env=env).returncode)
