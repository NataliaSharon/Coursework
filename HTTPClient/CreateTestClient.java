import static org.junit.Assert.*;

import org.junit.Test;


public class CreateTestClient {

	@Test
	public void test() {
		
	}

	private void testCompilation(){
		ClientTests clientTests = new ClientTests(new G52APRClient());
		clientTests.runTests("www.google.com");
	}
	
}
