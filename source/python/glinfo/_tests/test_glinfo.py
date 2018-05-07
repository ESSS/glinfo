from __future__ import absolute_import, division, print_function, unicode_literals


def test_glinfo():
    import subprocess
    print(subprocess.check_output('glinfo'))
