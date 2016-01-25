public class Location {

	int x;
	int y;
	Direction direction;

	public Location(int x, int y, Direction direction) {
		this.x = x;
		this.y = y;
		this.direction = direction;
	}

	public int getx() {

		return x;
	}

	public int gety() {

		return y;
	}

	public Direction getDirection() {

		return direction;
	}
}
