#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# libfrontg8 documentation build configuration file, created by
# sphinx-quickstart on Mon Aug 29 17:06:57 2016.
#
# This file is execfile()d with the current directory set to its
# containing dir.
#
# Note that not all possible configuration values are present in this
# autogenerated file.
#
# All configuration values have a default; values that are commented out
# serve to show the default.

# If extensions (or modules to document with autodoc) are in another directory,
# add these directories to sys.path here. If the directory is relative to the
# documentation root, use os.path.abspath to make it absolute, like shown here.
#
import os
import sys
import subprocess

on_rtd = os.environ.get('READTHEDOCS', None) == 'True'

if not on_rtd:
    import sphinx_rtd_theme
    html_theme = 'sphinx_rtd_theme'
    html_theme_path = [sphinx_rtd_theme.get_html_theme_path()]
else:
    subprocess.call('cd ../ && doxygen', shell=True)

sys.path.append(os.path.abspath("ext/breathe/"))
extensions = ['breathe']

breathe_projects = { "libfrontg8": os.path.abspath("../build/xml") }
breathe_default_project = "libfrontg8"

templates_path = ['_templates']

source_suffix = '.rst'

master_doc = 'index'

project = 'libfrontg8'
copyright = '2016, Felix Morgner'
author = 'Felix Morgner'

version = '0.1'
release = '0.1.0'

language = None

highlight_language = 'c'

exclude_patterns = ['build', 'Thumbs.db', '.DS_Store', 'ext']

pygments_style = 'sphinx'

todo_include_todos = False

html_logo = "_static/logo.png"
html_static_path = ['_static']

htmlhelp_basename = 'libfrontg8doc'

man_pages = [
    (master_doc, 'libfrontg8', 'libfrontg8 Documentation',
     [author], 1)
]

rst_epilog = '.. |project_name| replace:: **%s**' % project
