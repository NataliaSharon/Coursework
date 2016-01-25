import java.io.BufferedReader;
import java.io.InputStreamReader;

public class TestMain {

	Command newCommand = null;
	Response response = null;
	String numberInput = null;

	private static BufferedReader brd = new BufferedReader(
			new InputStreamReader(System.in));
	private static String input;

	public static void main(String[] args) {
		Rover curiosity = new Rover();
		TestMain testMain = new TestMain();
		testMain.beginExploration(curiosity);
	}

	public void beginExploration(Rover curiosity) {

		// string responses
		String ErrorResponse = ("TestMain::generateCommand, parse error: ");
		String ICO = ("incorrect command option");
		String ICL = ("incorrect command length");
		String IRT = ("incorrect rotation type");
		String ITV = ("incorrect temperature value");
		String IMV = ("incorrect move value");
		String Q = ("Quitting");
		String output = (">");

		char oldArguement = '0';
		char space = ' ';
		char oldCommand = '0';

		prompt(output);
		String userInput = readString();
		int length = userInput.length();
		boolean error = false;
		boolean notInt = false;

		if (length == 1) {
			oldCommand = userInput.charAt(0);
		} else if (((userInput.charAt(0) == 'M') || (userInput.charAt(0) == 'm'))
				&& (length >= 3)) {

			oldCommand = userInput.charAt(0);
			space = userInput.charAt(1);
			oldArguement = userInput.charAt(2);

			// if argument to M is a negative number
			if (userInput.charAt(2) == '-') {
				numberInput = "-";
				for (int i = 3; i < length; i++) {
					numberInput = numberInput + userInput.charAt(i);
					if (!Character.isDigit(userInput.charAt(i))) {
						notInt = false;
					}
				}
			} else { // if argument to M is a positive number
				numberInput = "";
				for (int i = 2; i < length; i++) {
					numberInput = numberInput + userInput.charAt(i);
					if (!Character.isDigit(userInput.charAt(i))) {
						notInt = false;
					}
				}
			}

			// if there was a non integer in the m argument then this is an
			// error
			if (notInt = false) {
				prompt(ErrorResponse + IMV + " " + numberInput);
				error = true;
			}

		} else if (length == 3) {
			oldCommand = userInput.charAt(0);
			space = userInput.charAt(1);
			oldArguement = userInput.charAt(2);
		} else {
			prompt(ErrorResponse + ICL);
			error = true;
		}

		if (error == false) {

			if (space == ' ') {
				char command = Character.toUpperCase(oldCommand);
				char arguement = Character.toUpperCase(oldArguement);

				if (length == 1) {
					switch (command) {

					case 'P':
						newCommand = new GetPressureCommand();
						printResponse(curiosity);
						break;

					case 'L':
						newCommand = new GetLocationCommand();
						printResponse(curiosity);
						break;

					case 'Q':
						prompt(Q);
						System.exit(0);
						break;

					default:
						prompt(ErrorResponse + ICO);
						break;
					}
				}

				if (length == 3) {
					switch (command) {

					case 'P':
					case 'L':
					case 'Q':
						prompt(ErrorResponse + ICL);
						break;

					case 'R':
						if (arguement == 'L') {
							newCommand = new RotateCommand(Rotation.LEFT);
							printResponse(curiosity);
						} else if (arguement == 'R') {
							newCommand = new RotateCommand(Rotation.RIGHT);
							printResponse(curiosity);
						} else if (arguement == 'A') {
							newCommand = new RotateCommand(Rotation.AROUND);
							printResponse(curiosity);

						} else {
							prompt(ErrorResponse + IRT + " " + oldArguement);
						}
						break;

					case 'T':
						boolean isC = true;
						if (arguement == 'C') {
							newCommand = new GetTemperatureCommand(isC);
							printResponse(curiosity);

						} else if (arguement == 'F') {
							isC = false;
							newCommand = new GetTemperatureCommand(isC);
							printResponse(curiosity);
						} else {
							prompt(ErrorResponse + ITV + " " + oldArguement);
						}

						break;
					// case M for if there are 3 places in the array

					case 'M':
						if (Character.isDigit(arguement)) {
							int moveInteger = Character
									.getNumericValue(arguement);
							newCommand = new MakeMoveCommand(moveInteger);
							printResponse(curiosity);
						} else {
							prompt(ErrorResponse + IMV + " " + numberInput);
						}
						break;

					default:
						prompt(ErrorResponse + ICO);
						break;
					}
				}

				if (length >= 4) {
					switch (command) {

					case 'M':
						int moveInteger = Integer.parseInt(numberInput);
						newCommand = new MakeMoveCommand(moveInteger);
						printResponse(curiosity);
						break;

					default:
						prompt(ErrorResponse + ICO);
						break;
					}
				}
			} else {
				prompt(ErrorResponse + ICO);
			}

		}
		System.out.println();
		beginExploration(curiosity);
	}

	public void printResponse(Rover curiosity) {
		response = curiosity.receiveCommand(newCommand);
		prompt(response.outputResponse);
	}

	public static void prompt(String s) {
		System.out.print(s + " ");
	}

	public static String readString() {
		String retStr = null;
		try {
			retStr = brd.readLine();
		} catch (Exception e) {
			System.out.println("Exception: Could not read a string from input");
		}
		return retStr;
	}

}
