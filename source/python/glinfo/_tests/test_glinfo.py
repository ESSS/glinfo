from __future__ import absolute_import, division, print_function, unicode_literals

import subprocess


def test_glinfo():
    '''
    Test that the output of `glinfo` has the expected format.
    '''
    output = subprocess.check_output('glinfo')
    lines = output.split('\n')

    assert len(lines) == 4
    assert lines[0].startswith('LibGL Vendor:')
    assert lines[1].startswith('Renderer:')
    assert lines[2].startswith('Version:')
    assert lines[3].startswith('Shading Language:')


def test_glinfo_file(tmpdir):
    '''
    Test that passing the '-f' parameter to `glinfo` writes the GL information to a file. The
    contents should be exactly the same as the contents written to standard output.
    '''
    filepath = tmpdir.join('output.txt')
    assert not filepath.check()

    output = subprocess.check_output(['glinfo', '-f', unicode(filepath)], universal_newlines=True)
    assert filepath.check()
    assert output == filepath.read_text('utf-8')
