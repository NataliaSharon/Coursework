// TODO: Auto-generated Javadoc
/**
 * The Interface IFlight.
 *
 * @author syn
 * 
 * Interface for the Flight class.
 * 
 * Do not modify this class. Make sure that your Flight.java class implements this interface.
 * You may wish to add additional methods to your Flight class which is expected, but do not modify this class.
 */

public interface IFlight {
	
	/**
	 * Gets the destination.
	 *
	 * @return the destination as a String
	 */
	public abstract String getDestination();

	/**
	 * Gets the time of departure.
	 *
	 * @return the departure time as a string
	 */
	public abstract String getTime(); 

	/**
	 * Returns the number of rows in that class
	 *
	 * @param rowClass true for club class, false for economy class.
	 * @return int representing the number of rows in that class.
	 */
	public abstract int numRows(boolean rowClass); 

	/**
	 * Returns the number of columns in that class
	 *
	 * @param rowClass true for club class, false for economy class.
	 * @return int representing the number of columns in that class.
	 */
	public abstract int numCols(boolean rowClass); 
	
	/**
	 * Sets the seat at the specified location to hold the specified person object
	 *
	 * @param loc the location
	 * @param person the person in the location
	 */
	public abstract void addSeatBooking(Location loc, Person person); 

	/**
	 * Checks if is seat empty.
	 *
	 * @param loc the location of the seat to check
	 * @return true, if is seat empty
	 */
	public abstract boolean isSeatEmpty(Location loc); 

	/**
	 * Gets the next available aisle seat, defined as the topmost, leftmost seat which has
	 * no person assigned to it and fulfills the requirement of an aisle seat.
	 *
	 * @param rowClass the row class (True for club class, false for economy class)
	 * @return the next available aisle seat. If there are none available, should return null.
	 */
	public abstract Location getNextAvailableAisleSeat(boolean rowClass);

	/**
	 * Gets the next available window seat, defined as the topmost, leftmost seat which has
	 * no person assigned to it and fulfills the requirement of a window seat.
	 *
	 * @param rowClass the row class (True for club class, false for economy class)
	 * @return the next available window seat. If there are none available, should return null.
	 */
	public abstract Location getNextAvailableWindowSeat(boolean rowClass);

	/**
	 * Gets the next available seat, defined as the topmost, leftmost seat which has
	 * no person assigned to it.
	 *
	 * @param rowClass the row class (True for club class, false for economy class)
	 * @return the next available seat. If there are none available, should return null.
	 */
	public abstract Location getNextAvailableSeat(boolean rowClass); 

	/**
	 * Prints the manifest.
	 */
	public abstract void printManifest(); 

	/**
	 * Prints the seating plan.
	 *
	 * @param rowClass the row class (True for club class, false for economy)
	 */
	public abstract void printSeatingPlan(boolean rowClass);

}