#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
import os
import sys
import subprocess

sys.path.append(os.path.abspath('ext/breathe/'))

subprocess.call('cd ../ && doxygen', shell=True)

if not os.environ.get('READTHEDOCS', None) == 'True':
    html_theme = 'sphinx_rtd_theme'

extensions = ['breathe']

breathe_projects = { 'libfrontg8': os.path.abspath('../build/xml') }
breathe_default_project = 'libfrontg8'
breathe_domain_by_extension = {
    'h' : 'c',
    'hpp': 'cpp',
}

templates_path = ['_templates']
source_suffix = '.rst'
master_doc = 'index'

project = 'libfrontg8'
copyright = '2016, Felix Morgner'
author = 'Felix Morgner'

version = '0.1'
release = '0.1.0'

language = 'en'

exclude_patterns = [
    'build',
    'Thumbs.db',
    '.DS_Store',
    'ext',
]

pygments_style = 'sphinx'

todo_include_todos = False

html_logo = '_static/logo.png'
html_static_path = ['_static']

htmlhelp_basename = 'libfrontg8doc'

man_pages = [
    (master_doc, 'libfrontg8', 'libfrontg8 Documentation',
     [author], 1)
]

rst_epilog = '.. |project_name| replace:: **%s**' % project

primary_domain = 'cpp'
