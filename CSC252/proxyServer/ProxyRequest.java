import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.Socket;
import java.net.URL;
import java.net.URLConnection;
import java.util.List;
import java.util.Map.Entry;
import java.util.StringTokenizer;


public class ProxyRequest extends Thread{
	
	private Socket socket;
	static int numThreads = 0;
	
	public ProxyRequest(Socket socket){
		super("Proxy Request");
		this.socket = socket;
		numThreads++;
	}
	
	@Override
	public void run(){
		
		try {
			//Opens input and output streams to the client making the request
            DataOutputStream out = new DataOutputStream(socket.getOutputStream());
            BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            
            boolean firstLine = true;
            String clientInput, address = "";
            
            //Read each line of the request from the client
            while ((clientInput = in.readLine()) != null) {
                //Parse each line of the request
            	try {
                    StringTokenizer tokenizer = new StringTokenizer(clientInput);
                    tokenizer.nextToken();
                    System.out.println("REQUEST F/CLIENT == " + clientInput);	//Output request line to server log console
                } catch (Exception e) {
	                    break;	//Break after no more header lines are entered. Essentially breaks when '\n' is enetered
                }
            	//Get the URL Address of request out of the first line of Header files
                if (firstLine) {
                    String[] header = clientInput.split(" ");
                    firstLine = false;
                    if(header[0].equalsIgnoreCase("GET")){	//This proxy server only accepts GET requests.
                    	address = header[1];
                    }
                    else{
                    	numThreads--;
                		System.out.println("Request End");
                		System.out.println("Threads Still Running = " + numThreads);
                    	return;
                    }
                }
            }

            BufferedReader reader = null;
            InputStream is = null;
            try {
            	//Opens Connection to requested page
                URLConnection urlConnection = new URL(address).openConnection();
                
                //If connection is not chunked
                if (urlConnection.getContentLength() > 0) {
                    System.out.println("Processing Stream: Content-length = " + urlConnection.getContentLength());
                	try {
                		//opens stream from requested page
                        is = urlConnection.getInputStream();
                        
                        //Array of bytes to hold incoming data from requested page
                        byte[] buffer = new byte[50000]; //0.05 MB == Buffer
                        
                        int amount; 	//Amount of bytes read in to the byte array. Will be 0.05 MB unless length left is less than 0.05MB
                        while ((amount = is.read( buffer, 0, buffer.length)) != -1)
                        {
                          out.write(buffer,0,amount);	//Write each buffer to the outpur stream
                        }
                        out.flush();	//Flush the output stream after writing all of the bytes
                    } catch (IOException e) {
                        System.out.println("Exception: NOT CHUNKED...");
                        e.printStackTrace();
                    }
                }
                //Chunked Connection
                else{
                	System.out.println("Processing Chunked Stream");
                	try {
                		//opens stream from requested page
                        is = urlConnection.getInputStream();
                        //Use a buffered reader to read chunked data line by line
                        reader = new BufferedReader(new InputStreamReader(is));
                        
                        String chunkLine;	//Each line of the chunked response
                        while((chunkLine = reader.readLine()) != null){
                        	byte[] buffer = chunkLine.getBytes(); //Converts the line received to bytes in order to send to client
                        	out.write(buffer, 0,buffer.length);	//Write each buffer to the output stream
                        }
                        out.flush();	//Flush the output stream after writing all of the bytes
                    } catch (IOException e) {
                    	System.out.println("Exception: CHUNKED...");
                    	e.printStackTrace();
                    }
                }
                
                
            } catch (Exception e) {
            	System.out.println("Exception: generic...");
            	e.printStackTrace();
                out.writeBytes("");
            }
            
            //Close out all resources, So thread doesn't leak resources
            if (socket != null)
                socket.close();
            if(reader != null)
                reader.close();
            if(is != null)
            	is.close();
            if (in != null)
                in.close();
            if (out != null)
                out.close();
            
		} catch(IOException e){
			System.out.println("Exception: FINAL IOE...");
        }
		
		//Update Proxy Server console log, and reduce thread count
		System.out.println("Completed Request");
		numThreads--;
		System.out.println("Threads Still Running = " + numThreads);
	}
}
