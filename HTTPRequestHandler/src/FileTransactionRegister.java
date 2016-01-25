import java.io.File;
import java.util.Date;

public class FileTransactionRegister {

	private String read;
	private String path;
	private TransactionRegister tr;

	public FileTransactionRegister(String read, String path) {
		this.read = read;
		this.path = path;

		// create instance of a transactionRegister
		tr = new TransactionRegister(read, path);
		// if argument = -R then delete file
		if (read.equals("-R")) {
			new File(path).delete();
		}
		
		//call write and write in starting details
		write(new Date().toString() + ", $, starting register\n");

	}

	public String getRead() {
		
		return read;
	}

	public String getPath() {
		
		return path;
	}

	public void write(String transaction) {

		tr.write(transaction);

	}

}
