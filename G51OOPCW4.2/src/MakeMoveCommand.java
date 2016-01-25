public class MakeMoveCommand extends Command {
	private int distance;

	public MakeMoveCommand(int distance) {
		this.distance = distance;
	}

	public int getDistance() {
		return distance;
	}

}
