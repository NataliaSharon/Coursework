/**
 * 
 * @author azp
 * 
 *         Used to wrap up two ints and a boolean so they can be returned or passed together.
 *         
 *         You should not need to modify this class.
 * 
 */

public class Location {
	
	
	private int row;
	private int col;
	boolean isClub; // true => club, false => economy 
	
	public Location (int row, int col, boolean isClub) {
		this.row = row;
		this.col = col;
		this.isClub = isClub;
	}
	
	public boolean isClub() {
		
		return this.isClub;
	}
	
	public int getRow() {
	
		return row;
	}
	
	public int getCol() {
		
		return col;
	}
	
}
