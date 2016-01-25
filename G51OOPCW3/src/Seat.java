public class Seat {

	private boolean isWindowSeat;
	private boolean isAisleSeat;
	private String name;
	private String nationality;
	private boolean isTaken;

	public Seat(boolean isWindowSeat, boolean isAisleSeat) {
		this.isWindowSeat = isWindowSeat;
		this.isAisleSeat = isAisleSeat;
		this.name = "";
		this.nationality = "";
		this.isTaken = false;
	}

	public String getPerson() {
		return name;
	}

	public boolean isWindow() {

		return isWindowSeat;
	}

	public boolean isAsisle() {

		return isAisleSeat;
	}

	public boolean getTaken() {

		return isTaken;
	}

	public void setPerson(Person person) {
		this.name = person.getName();
		this.nationality = person.getNationality();
		this.isTaken = true;
	}
	
	public String getNationality() {
		// TODO Auto-generated method stub
		return nationality;
	}

}
