#include "ClientSocket.h"
#include "SocketException.h"
#include <iostream>
#include <string>
#include "simpio.h"
#include "genlib.h"

// int main ( int argc, int argv[] )
int main()
{
    try {
	ClientSocket client_socket ( "localhost", 30004 );
	string reply;
	string cmd;

	while (true) {
	    cout << "> ";
	    cmd = GetLine();
	    try {
		if (cmd == "") break;
		client_socket << cmd;
		client_socket >> reply;
	    }
	    catch ( SocketException& ) {}
	std::cout << "Response from server:\n\"" << reply << "\"\n";
	}
    }
    catch ( SocketException& e ) {
	std::cout << "Client exception: " << e.description() << "\n";
    }

    return 0;
}
