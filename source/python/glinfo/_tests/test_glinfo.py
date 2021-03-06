from __future__ import absolute_import, division, print_function, unicode_literals

import subprocess
import six


def test_glinfo():
    '''
    Test that the output of `glinfo` has the expected format.
    '''
    output = subprocess.check_output('glinfo').decode('ascii')
    lines = output.split('\n')

    # The output is either the complete GL info or a single line with an error message.
    if len(lines) == 4:
        assert lines[0].startswith('LibGL Vendor:')
        assert lines[1].startswith('Renderer:')
        assert lines[2].startswith('Version:')
        assert lines[3].startswith('Shading Language:')
    else:
        assert len(lines) == 1
        assert lines[0] == 'ERROR: Unable to create an OpenGL context.'


def test_glinfo_file(tmpdir):
    '''
    Test that passing the '-f' parameter to `glinfo` writes the GL information to a file. The
    contents should be exactly the same as the contents written to standard output.
    '''
    filepath = tmpdir.join('output.txt')
    assert not filepath.check()

    output = subprocess.check_output(['glinfo', '-f', six.text_type(filepath)], universal_newlines=True)
    assert filepath.check()
    assert output == filepath.read_text('utf-8')
