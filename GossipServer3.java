import java.net.InetAddress;
import java.net.UnknownHostException;
import java.io.*;
import java.net.*;
import java.util.Date;

public class GossipServer3

{
  public static void main(String[] args) throws Exception
  {
      ServerSocket sersock = new ServerSocket(26272);
      System.out.println("Server  ready for chatting");
      Socket sock = sersock.accept( );                          
      BufferedReader keyRead = new BufferedReader(new InputStreamReader(System.in));

      OutputStream ostream = sock.getOutputStream();
      PrintWriter pwrite = new PrintWriter(ostream, true);      
      InputStream istream = sock.getInputStream();
      BufferedReader receiveRead = new BufferedReader(new InputStreamReader(istream));

      String receiveMessage, sendMessage;
	
	Date d=new Date();
	
	try {

	InetAddress inetAddress = InetAddress.getLocalHost();
	System.out.println("IP address: "+inetAddress.getHostAddress());
	System.out.println("Hostname : "+inetAddress.getHostName());	
	
	}
	catch(UnknownHostException unknownHostException)
	 {
	
	unknownHostException.printStackTrace();
	}
	
	String s="Current Date & Time on Server is:"+d;
	System.out.println(s);
	PrintWriter toclient=new PrintWriter(sock.getOutputStream(),true);
        toclient.print(s);
	
	toclient.close();	

	while(true)

      {
	if((receiveMessage = receiveRead.readLine()) != null)  

        {

           System.out.println("client : " + receiveMessage);
        }        

        sendMessage = keyRead.readLine();
	System.out.println("server : "+ sendMessage);
        pwrite.println(sendMessage);
        pwrite.flush();

      }             
    }                    

}

