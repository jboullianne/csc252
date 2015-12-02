                  ___ ___   _   ___    __  __ ___                
  ___ ___ ___ ___| _ \ __| /_\ |   \  |  \/  | __|__ ___ ___ ___ 
 |___|___|___|___|   / _| / _ \| |) | | |\/| | _|___|___|___|___|
                 |_|_\___/_/ \_\___/  |_|  |_|___|               
                                                                 

//////////////////////////////////////////////////////////////////

   ___                                  _    __      __   _    
  / __|___ _ _  __ _  _ _ _ _ _ ___ _ _| |_  \ \    / /__| |__ 
 | (__/ _ \ ' \/ _| || | '_| '_/ -_) ' \  _|  \ \/\/ / -_) '_ \
  \___\___/_||_\__|\_,_|_|_|_| \___|_||_\__|   \_/\_/\___|_.__/
 | _ \_ _ _____ ___  _  / __| ___ _ ___ _____ _ _              
 |  _/ '_/ _ \ \ / || | \__ \/ -_) '_\ V / -_) '_|             
 |_| |_| \___/_\_\\_, | |___/\___|_|  \_/\___|_|               
                  |__/                                         

//////////////////////////////////////////////////////////////////

CSC252: Computer Organization
Lab Assignment #5: Concurrent Web Proxy Server
Spring 2015

TEAM MEMBERS:
	
	- Jean-Marc Boullianne
		UserID: jboullia
		Email:	jboullia@u.rochester.edu

	- Aurek Ransom
		UserID: aransom
		Email:	aransom@u.rochester.edu


FILES INCLUDED:
	
	ProxyServer.java		: Source code for main server loop. Handles incoming connections, and starts new threads. 
	ProxyServer.class		: Class file for ProxyServer.java
	ProxyRequest.java		: Thread class for handling new proxy requests from clients (Ensures the web proxy's concurrency).
	ProxyRequest.class		: Class file for ProxyRequest.java

HOW TO COMPILE:

	1.	Open terminal in directory of source code.
	2.	Run make file.

HOW TO RUN:
	
	1.	Follow steps to compile server.
	2. 	Open terminal in directory of compiled source code.
	3. 	Type command 'java ProxyServer <port_number><enter>'
	4.	The Proxy Server is now ready for requests.

ABOUT PROGRAM:


