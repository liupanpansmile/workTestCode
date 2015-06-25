

public class ThreadJni {
	
	/*
	 * 通过JNI创建线程，然后线程launch另外进程,并返回线程的ＩＤ
	 * */
	public native long CreateThread(String applicationName,String cmdLine) ;
	
	static 
	{
		System.loadLibrary("ThreadJni");
	}
	public static void main (String[] args)
	{
		String applicationName = "D:\\ffAgent001\\ffAgent001\\38.0.5\\firefox.exe" ;
		String cmdLine = "-no-remote -profile D:\\ffAgent001\\ffAgent001\\38.0.5\\oenapm_profile_1 -tsport 8800 about:blank " ;
		ThreadJni obj = new ThreadJni() ;
		long processId = obj.CreateThread(applicationName,cmdLine);
		
		System.out.println("ProcessId = " + processId);
	}
}
