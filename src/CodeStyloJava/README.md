# Setup
- Java 8 or higher
- OpenJDK is usable, so far no problems

# About
- This directory contains some modifications from the github repository by Aylin Caliskan.
	- Only the Naive Baseline directory is needed
	- See https://github.com/calaylin/CodeStylometry for the original repository.

- the Naive Baseline directory provides code to get lexical and layout features, as mentioned in paper
	- The naive baseline project is very readable, happy to see that ;)
	- A problem, however, is that some features from some authors were not correctly extracted, as the features
	are extracted via a regex. We thus used the clang compiler for some features.

- Modifications:
	- We excluded some features that we extract via clang
		- For example, the branching factor can be determined more reliably via a compiler than a regex.
	- We fixed some encoding stuff we had problems with
	- We adapted the driver class to accept arguments now
		- It is now possible to add either the path of the different authors or a particular source file directly.

# Getting started

- Include this project as a Java project. The following description is based
on IDEA as IDE (just to outline the principle, other workflows work equally,
	you just have to create a callable jar file).
	- make sure you import the libraries under SCAA/
		- If you have problems with the libraries, go [here](https://github.com/calaylin/CodeStylometry)
		and download the full SCAA directory again. Put it under *CodeStyloJava*.
	- a first test: compile everything with Driver.java as main class
- Now create a JAR file
	- maybe the following [link](https://www.jetbrains.com/help/idea/packaging-a-module-into-a-jar-file.html#)
	helps you.
	- You probably get a jar file with the following path CodeStyloJava/out/artifacts/CodeStyloJava_jar/CodeStyloJava.jar
	- the absolute path to this file is important.
- Add path information:
	- for *data/extractfeatures_single.sh*, you need to pass the
	path to the jar file above.
		- Either edit the script and add the path
			in the 7th line for the CMD_DIR_NAIVEBASELINE variable.
		- Or add the path as a environment variable. You can do that by adding the following line in the ~/.bashrc file:
	```
	export CMD_DIR_NAIVEBASELINEJAR=<path-to-repo>/src/CodeStyloJava/out/artifacts/CodeStyloJava_jar/CodeStyloJava.jar"
	```
	- For the python project, add the full path to the 'naivebaselinecmd'
	variable in the config.ini file.
