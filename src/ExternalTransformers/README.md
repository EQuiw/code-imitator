# External Transformers 

- Here, we put stand-alone tools that we can also use to rewrite code, e.g.
 we use Include-What-You-Use to detect what unused headers we can remove and
what headers we should include.

Consider that each external transformer is optional, so if you don't set the environment
variables, we will skip the respective transformer during evasion attack. 
In this way, you can quickly set up our project and do some transformations, and if necessary,
add the helpful external transformers later.

## Overview

1. Include-What-You-Use
- Download IWYU from the official website:
https://github.com/include-what-you-use/include-what-you-use
- Follow the official instructions there
- Add the path to build dir to config.ini in PyProject.

2. no other external transformers, yet



## How to add your own external transformer
- modify csv in this directory
- create own Python class that inherits from TransformerBase
- add code to `__load_external_transformers` in TransformerHandler 
- add path to dir of executable to config.ini and Configuration.py

