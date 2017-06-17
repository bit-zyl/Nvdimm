package com.yh;

public class NvdimmUtils {
	
	// gcc -fPIC -D_REENTRANT -I /usr/java/jdk1.8.0_111/include -I /usr/java/jdk1.8.0_111/include/linux -I /usr/include -c Write2Nvdimm.c
	
	//gcc -shared Write2Nvdimm.o -lArxcisAPI -o libWrite2Nvdimm.so
	
	public static final NvdimmUtils nv;

	static {
		System.loadLibrary("Write2NvdimmTest");
		nv = new NvdimmUtils();
//		System.out.println(System.getProperty("java.library.path"));
//		System.out.println(System.getProperty("user.home"));
	
//		System.loadLibrary("ArxcisAPI");
		
//		System.load("/root/Desktop/eclipse_workspace/Haha/src/libWrite2Nvdimm.so");
	}

	
	private NvdimmUtils(){}
	
//	public static NvdimmUtils getInstace(){
//		if (nv == null){
//			nv = new NvdimmUtils();
//		}
//		return nv;
//	}
	
	public void put(byte[]b,int off, int leng){
		nv.write(b,off,leng);
	}
	
	public native void write(byte[]b,int off, int leng);
	


	public static void main(String[] args) {
		// TODO Auto-generated method stub
		byte b []= new byte[1024];
		b[0]='a';
		b[1]='2';
		b[2]='3';
		NvdimmUtils nv = new NvdimmUtils();
		nv.write(b,0,3);
		System.out.println(b[0]);

	}

}
