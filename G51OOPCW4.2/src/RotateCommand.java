public class RotateCommand extends Command {

	private Rotation rotate;

	public RotateCommand(Rotation rotate) {

		this.rotate = rotate;
	}

	public Rotation getRotation() {

		return rotate;
	}
}
