import java.io.*;

import java.net.*;

public class ServerChat

{
	public static void main(String[] args) throws Exception
	{
	ServerSocket sersock=new ServerSocket(6776);
	System.out.println("Server ready for chatting");
	Socket sock = sersock.accept( );

	BufferedReader keyRead = new BufferedReader(new 
InputStreamReader(System.in));

	OutputStream ostream=sock.getOutputStream();
	PrintWriter pwrite=new PrintWriter(ostream,true);

	InputStream istream = sock.getInputStream();
	BufferedReader receiveRead = new BufferedReader(new 
InputStreamReader(istream));

	String receiveMessage, sendMessage;
	
	while(true)
	{
	if((receiveMessage = receiveRead.readLine()) != null)
	{
		System.out.println(receiveMessage);

		if(receiveMessage.equals("assalamualaikum"))
		{
		sendMessage="waalaikumussalam";
		pwrite.println(sendMessage);
		pwrite.flush();
		}
		else
		{
		sendMessage="are you a muslim?";
		pwrite.println(sendMessage);
		pwrite.flush();
		}
	}	
	sendMessage = keyRead.readLine();
	pwrite.println(sendMessage);
	pwrite.flush();
	}
	}
}
		
