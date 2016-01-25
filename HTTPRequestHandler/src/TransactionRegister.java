import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;

public class TransactionRegister {

	private String read;
	private String path;

	public TransactionRegister(String read, String path) {
		this.read = read;
		this.path = path;
	}

	public void write(String transaction) {

		// convert transaction to string
		String transactionDetails = transaction.toString();


		// get file
		File file = new File(path);

		// create file if it does not exist
		if (!file.exists()) {
			try {
				file.createNewFile();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}

		// append the data onto the file
		FileWriter fileWriter = null;
		try {
			fileWriter = new FileWriter(file, true);
			BufferedWriter bufferWritter = new BufferedWriter(fileWriter);
			bufferWritter.write(transactionDetails);
			bufferWritter.close();
		} catch (IOException e) {
			e.printStackTrace();
		}

	}
}
