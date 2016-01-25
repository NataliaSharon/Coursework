import java.io.BufferedReader;
import java.io.InputStreamReader;

public class FlightBookingSystem {

	// initialising variables
	private Flight[] flights;
	String destination;
	String departureTime;
	String name;
	String nationality;

	// when creating a flight, these are the number of rows there are
	static int CCrows = 0;
	static int ECrows = 0;

	// entered in by user to specify which row/column/seat they want
	int rowNumber;
	int columnNumber;
	char seatType;
	int seatSelection;

	int flightCounter;
	int peopleCounter = 0;

	private static BufferedReader brd = new BufferedReader(
			new InputStreamReader(System.in));
	private static String input;

	public FlightBookingSystem(int i) {
		flightCounter = 0;
		flights = new Flight[i];

	}

	public static void main(String[] args) {
		// Do not modify this method!
		FlightBookingSystem fbs = new FlightBookingSystem(10);
		fbs.runMainMenu();
	}

	private void runMainMenu() {

		char charInput;

		// if there is not at least one flight booking then (else go to
		// flightBookingMenu()

		// first main menu
		System.out.println();
		System.out.println("Flight Booking Menu");
		System.out.println("===================");
		System.out.println("1) Create Flight");
		System.out.println("Q) Quit");
		System.out.println();
		System.out.print("Enter your choice: ");
		charInput = getChar();

		// case statements to determine next procedure
		switch (charInput) {
		case 'q':
		case 'Q':
			System.out.println("Quitting....");
			System.exit(0);
			break;

		case '1':
			flightCreatorMenu();
			break;

		default: // if any other characters are input
			System.out.println("ERROR: Invalid menu choice!");
			runMainMenu();
		}
	}

	public void flightCreatorMenu() {
		System.out.println();
		System.out.println("Flight Creator");
		System.out.println("==============");
		System.out.print("Enter destination: ");
		destination = readString();
		System.out.print("Enter departure time: ");
		departureTime = readString();
		System.out.println();
		int clubClassRows = clubClassRows();
		int economyClassRows = economyClassRows();
		flights[flightCounter++] = new Flight(clubClassRows, economyClassRows,
				destination, departureTime);

		flightBookingMenu();

	}

	public int clubClassRows() {

		System.out.println("Aeroplane Details");
		System.out.println("==============");
		System.out.print("Enter number of rows in Club Class: ");
		CCrows = readInt();

		if (CCrows < 0 || CCrows > 4) {
			System.out.println("ERROR: Invalid Row Count");
			runMainMenu();
		}

		return CCrows;
	}

	public int economyClassRows() {
		System.out.print("Enter number of rows in Economy Class: ");
		ECrows = readInt();

		if (ECrows < 0 || ECrows > 6) {
			System.out.println("ERROR: Invalid Row Count");

			runMainMenu();
		}
		return ECrows;

	}

	public void flightBookingMenu() {

		char charInput;
		int flightSelection;

		System.out.println();
		System.out.println("Flight Booking Menu");
		System.out.println("==============");
		System.out.println("1) Create Flight");
		System.out.println("2) Make Booking on Flight");
		System.out.println("3) Print A Flight's Manifest");
		System.out.println("Q) Quit");
		System.out.println();
		System.out.print("Enter your choice: ");
		charInput = getChar();

		switch (charInput) {
		case 'q':
		case 'Q':
			System.out.println("Quitting....");
			System.exit(0);
			break;

		case '1':
			flightCreatorMenu();
			break;

		case '2':
			flightSelection = availableFlights();
			makeBooking(flightSelection);
			break;

		case '3':
			flightSelection = availableFlights();
			flights[flightSelection].printManifest();
			break;

		default: // if any other characters are input
			System.out.println("ERROR: Invalid menu choice!");
			System.out.println();
			runMainMenu();

		}

	}

	// when 2 or 3 is entered, list of available flights appears
	public int availableFlights() {

		int printFlights;
		int flightSelection;

		System.out.println();
		System.out.println("Available flights: ");

		for (printFlights = 0; printFlights < flightCounter; ++printFlights) {
			System.out.print("Flight number: " + printFlights);
			System.out.print(", Destination: "
					+ flights[printFlights].destination);
			System.out.print(", Departure time: "
					+ flights[printFlights].departureTime);
			System.out.println();
		}
		System.out.print("Enter flight number: ");
		flightSelection = readInt();
		System.out.println();

		while (flightSelection > flightCounter && flightSelection < 0) {
			System.out.println("ERROR: Invalid menu choice!");
			availableFlights();
		}

		return flightSelection;
	}

	// if 2 is entered; make booking - select seat type
	public void makeBooking(int flightSelection) {

		System.out.println("Seat Type");
		System.out.println("=========");
		System.out.println();

		if (flights[flightSelection].getNextAvailableSeat(true) != null) {
			System.out.println("C) Book Club Class Seat");
		}

		if (flights[flightSelection].getNextAvailableSeat(false) != null) {
			System.out.println("E) Book Economy Class Seat");
		}

		System.out.print("Pick your seat type: ");
		seatType = getChar();

		if (seatType != 'c' && seatType != 'C' && seatType != 'e'
				&& seatType != 'E') {
			System.out.println("ERROR: Invalid menu choice!");
			System.out.println();
			makeBooking(flightSelection);
		}
		seatSelection(seatType, flightSelection);
	}

	// making booking - select which specific seat
	public void seatSelection(int seatType, int flightSelection) {

		boolean isClub = true;

		System.out.println("Seat Selection");
		System.out.println("==============");
		System.out.println();
		System.out.println("1) Pick Specific Seat");
		System.out.println("2) Any Window Seat");
		System.out.println("3) Any Aisle Seat");
		System.out.println("4) Any Seat");
		System.out.print("Enter Preference: ");
		seatSelection = readInt();

		if (seatSelection > 4 || seatSelection < 0) {
			System.out.println("ERROR: Invalid menu choice!");
			seatSelection(seatType, flightSelection);
		}

		if (seatType == 'e' || seatType == 'E') {
			isClub = false;
		} else if (seatType == 'c' || seatType == 'C') {
			isClub = true;
		}

		if (seatSelection == 1) {
			enterBooking(flightSelection, isClub);

		} else if (seatSelection == 2) {
			if (flights[flightSelection].getNextAvailableWindowSeat(isClub) == null) {
				bookAgain(flightSelection);
			} else {
				Location loc = flights[flightSelection]
						.getNextAvailableWindowSeat(isClub);
				createDetails(loc, flightSelection, isClub);
			}

		} else if (seatSelection == 3) {
			if (flights[flightSelection].getNextAvailableAisleSeat(isClub) == null) {
				bookAgain(flightSelection);
			} else {
				Location loc = flights[flightSelection]
						.getNextAvailableAisleSeat(isClub);
				createDetails(loc, flightSelection, isClub);

			}
		} else if (seatSelection == 4) {
			if (flights[flightSelection].getNextAvailableSeat(isClub) == null) {
				bookAgain(flightSelection);
			} else {
				Location loc = flights[flightSelection]
						.getNextAvailableSeat(isClub);
				createDetails(loc, flightSelection, isClub);
			}
		}
	}

	public void enterBooking(int flightSelection, boolean isClub) {

		flights[flightSelection].printSeatingPlan(isClub);
		boolean addCorrect = false;

		do {

			// validating the numbers entered
			do {
				System.out.print("Enter Row: ");
				rowNumber = readInt();

				if ((rowNumber > flights[flightSelection].numRows(isClub))
						|| (rowNumber < 0)) {
					System.out.println("ERROR: Invalid row number");
				}
			} while ((rowNumber > flights[flightSelection].numRows(isClub))
					|| (rowNumber < 0));

			do {
				System.out.print("Enter Column: ");
				columnNumber = readInt();

				if (columnNumber > flights[flightSelection].numCols(isClub)
						|| (columnNumber < 0)) {
					System.out.println("ERROR: Invalid column number");
				}
			} while ((columnNumber > flights[flightSelection].numCols(isClub))
					|| (columnNumber < 0));

			// checks if the seat is already taken
			Location loc = new Location(rowNumber, columnNumber, isClub);

			if (flights[flightSelection].isSeatEmpty(loc)) {
				addCorrect = false;
				System.out.println("ERROR: Seat already taken");
			} else {
				addCorrect = true;
			}

		} while (addCorrect == false);

		Location loc = new Location(rowNumber, columnNumber, isClub);
		createDetails(loc, flightSelection, isClub);
	}

	public void createDetails(Location loc, int flightSelection, boolean isClub) {

		System.out.println();
		System.out.print("Enter person's name: ");
		name = readString();
		System.out.print("Enter person's nationality: ");
		nationality = readString();

		Person person = new Person(name, nationality);
		flights[flightSelection].addSeatBooking(loc, person);

		System.out.println();
		bookAgain(flightSelection);

	}

	public void bookAgain(int flightSelection) {
		char bookAgain;

		do {
			System.out.print("Book another seat? (Y/N); ");
			bookAgain = getChar();

			if (bookAgain != 'y' && bookAgain != 'Y' && bookAgain != 'n'
					&& bookAgain != 'N') {
				System.out.println("ERROR: Invalid menu choice!");
			} else if (bookAgain == 'y' || bookAgain == 'Y') {
				makeBooking(flightSelection);
			} else if (bookAgain == 'n' || bookAgain == 'N') {
				flightBookingMenu();
			}

		} while (bookAgain != 'y' && bookAgain != 'Y' && bookAgain != 'n'
				&& bookAgain != 'N');
	}

	// following methods allows user to make input

	public static char getChar() {
		int retVal = (char) 0;
		try {
			input = brd.readLine();
			if (input.length() != 1)
				throw new Exception();
			retVal = (int) input.charAt(0);
			if (retVal < 32)
				throw new Exception();
		} catch (Exception e) {
			System.out
					.println("Exception: Could not getChar() from input stream");
		}
		return (char) retVal;
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

	public static int readInt() {
		int retVal = Integer.MAX_VALUE;
		try {
			input = brd.readLine();
			retVal = Integer.parseInt(input.trim());
		} catch (Exception e) {
			System.out.println("Exception: Could not parse \"" + input
					+ "\" as an int");
		}
		return retVal;

	}
}
