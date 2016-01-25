public class Flight implements IFlight {

	String destination;
	String departureTime;
	int clubClassRows;
	int economyClassRows;
	private Seat[][] ECseat;
	private Seat[][] CCseat;

	public Flight(int clubClassRows, int economyClassRows, String destination,
			String departureTime) {

		this.destination = destination;
		this.departureTime = departureTime;
		this.clubClassRows = clubClassRows;
		this.economyClassRows = economyClassRows;
		this.ECseat = new Seat[economyClassRows][6];
		this.CCseat = new Seat[clubClassRows][4];
		boolean window = false;
		boolean aisle = true;

		for (int i = 0; i < clubClassRows; ++i) {
			for (int j = 0; j < 4; ++j) {
				if (j == 0 || j == 3) {
					window = true;
				}

				this.CCseat[i][j] = new Seat(window, aisle);
				window = false;
			}
		}

		for (int i = 0; i < economyClassRows; ++i) {
			for (int j = 0; j < 6; ++j) {
				if (j == 0 || j == 5) {
					window = true;
				} else if (j == 2 || j == 4) {
					aisle = true;
				}

				this.ECseat[i][j] = new Seat(window, aisle);
				window = false;
				aisle = false;
			}
		}

	}

	public String getDestination() {

		return this.destination;
	}

	public String getTime() {

		return this.departureTime;
	}

	public int numRows(boolean rowClass) {
		if (rowClass) {
			return clubClassRows;
		} else {
			return economyClassRows;
		}
	}

	public int numCols(boolean rowClass) {

		if (rowClass) {
			return 4;
		} else {
			return 6;
		}
	}

	public void addSeatBooking(Location loc, Person person) {

		if (loc.isClub() == true) {
			this.CCseat[loc.getRow()][loc.getCol()].setPerson(person);
		} else {
			this.ECseat[loc.getRow()][loc.getCol()].setPerson(person);
		}
	}

	public boolean isSeatEmpty(Location loc) {
		if (loc.isClub() == true) {
			return this.CCseat[loc.getRow()][loc.getCol()].getTaken();
		} else {
			return this.ECseat[loc.getRow()][loc.getCol()].getTaken();
		}
	}

	public Location getNextAvailableWindowSeat(boolean rowClass) {

		for (int i = 0; i < this.numRows(rowClass); i++) {
			for (int j = 0; j < this.numCols(rowClass); j++) {
				if ((rowClass) && ((j == 0) || (j == 3))) {
					Location loc = new Location(i, j, rowClass);
					if (this.CCseat[i][j].isWindow()) {
						return loc;
					}
				} else if ((rowClass == false) && ((j == 0) || (j == 5))) {
					Location loc = new Location(i, j, rowClass);
					if (this.ECseat[i][j].isWindow()) {
						return loc;
					}

				}
			}
		}
		System.out.println("Sorry, no window seats left");
		return null;

	}

	@Override
	public Location getNextAvailableSeat(boolean rowClass) {

		for (int i = 0; i < this.numRows(rowClass); i++) {
			for (int j = 0; j < this.numCols(rowClass); j++) {
				if (rowClass == true) {
					Location loc = new Location(i, j, rowClass);
					if (this.CCseat[i][j].getTaken() == false) {
						return loc;
					}
				} else if (rowClass == false) {
					Location loc = new Location(i, j, rowClass);
					if (this.ECseat[i][j].getTaken() == false) {
						return loc;
					}
				}
			}
		}
		return null;
	}

	@Override
	public Location getNextAvailableAisleSeat(boolean rowClass) {
		for (int i = 0; i < this.numRows(rowClass); i++) {
			for (int j = 0; j < this.numCols(rowClass); j++) {
				if ((rowClass = true) && ((j == 1) || (j == 2))) {
					Location loc = new Location(i, j, rowClass);
					if (this.CCseat[i][j].isAsisle()) {
						return loc;

					}
				} else if ((rowClass = false) && ((j == 2) || (j == 3))) {
					Location loc = new Location(i, j, rowClass);
					if (this.ECseat[i][j].isAsisle()) {
						return loc;
					}

				}
			}
		}
		System.out.println("Sorry, no aisle seats left");
		return null;
	}

	public void printSeatingPlan(boolean rowClass) {

		int j;
		int i;

		if (rowClass) {
			System.out.println("   0 1 2 3");
		} else {
			System.out.println("  0 1 2 3 4 5");
		}
		// does not print X
		for (i = 0; i < numRows(rowClass); ++i) {
			System.out.print(i + ": ");
			for (j = 0; j < this.numCols(rowClass); ++j) {
				Location loc = new Location(i, j, rowClass);
				if (isSeatEmpty(loc) == false) {
					System.out.print("O ");
				} else {
					System.out.print("X ");
				}
			}
			System.out.println();
		}

	}

	@Override
	public void printManifest() {

		int i;
		int j;

		System.out.println("Flight Manifest");
		System.out.println("Destination: " + this.destination);
		System.out.println("Departure time: " + this.departureTime);
		System.out.println("Club Class passenger list: ");

		boolean value = true;

		for (i = 0; i < clubClassRows; i++) {
			for (j = 0; j < numCols(true); j++) {
				Location loc = new Location(i, j, true);
				if (this.CCseat[i][j].getPerson() != "") {
					if (isSeatEmpty(loc) == true) {
						value = false;
						System.out.println("Row: " + i + ", Column: " + j
								+ ", Name: " + this.CCseat[i][j].getPerson()
								+ ", Nationality: "
								+ this.CCseat[i][j].getNationality());
					}
				}
			}
		}
			
	
		if (value) {
			System.out.println("No passengers in Club Class");
		}

		System.out.println("Economy Class passenger list: ");
		value = true;
		
		for (i = 0; i < economyClassRows; i++) {
			for (j = 0; j < numCols(false); j++) {
				Location loc = new Location(i, j, false);
				if (this.ECseat[i][j].getPerson() != "") {
					if (isSeatEmpty(loc) == true) {
						value = false;
						System.out.println("Row: " + i + ", Column: " + j
							+ ", Name: " + this.ECseat[i][j].getPerson()
							+ ", Nationality: "
							+ this.ECseat[i][j].getNationality());
					}
				}
			}
		}
		
		if (value) {
			System.out.println("No passengers in Economy Class");
		}
	}
}
