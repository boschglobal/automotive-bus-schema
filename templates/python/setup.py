#***************************************************************************
# Copyright (c) 2021 for information on the respective copyright owner
# see the NOTICE file and/or the following repository:
#     https://github.com/boschglobal/automotive-bus-schema
#
# SPDX-License-Identifier: Apache-2.0
#***************************************************************************

import os
from setuptools import setup, find_packages


install_requires = [
    'flatbuffers',
]

PACKAGE_NAME = "automotive-bus-schema"

DESCRIPTION = """
Automotive Bus Schema
=====================

Generated Python Package containing generated code from the Automotive Bus Schema.
"""

setup(
    name = PACKAGE_NAME,
    version = os.getenv('PACKAGE_VERSION', 'devel'),
    author = "Timothy Rule",
    author_email = "Timothy.Rule@de.bosch.com",
    description = 'Automotive Bus Schema',
    long_description = DESCRIPTION,
    long_description_content_type = 'text/markdown',
    url = "https://github.com/boschglobal/automotive-bus-schema.git",
    license = "Apache-2.0",

    packages=find_packages(),
    include_package_data=True,

    python_requires='>=3.8',
    install_requires=install_requires,
    setup_requires=[],
    zip_safe=False,

    classifiers=[
        "License :: Apache-2.0",
        "Natural Language :: English",
        "Operating System :: POSIX :: Linux",
        "Programming Language :: Python :: 3.8",
        "Topic :: Software Development :: Simulation",
    ],
)
