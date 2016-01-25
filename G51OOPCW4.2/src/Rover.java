import java.util.ArrayList;

public class Rover {
	ArrayList<Response> Log = new ArrayList<Response>();

	public Rover() {

	}

	public void log(Response response) {
		Log.add(response);
	}

	public Response getLastResponse() {
		return Log.get(Log.size() - 1);
	}

	public ArrayList<Response> getLog() {
		return Log;
	}

	public Response receiveCommand(Command command) {
		Response response;
		response = null;

		switch (command.toString()) {

		case "GetTemperatureCommand":
			ThermometerAsset thermometerAsset = new ThermometerAsset(null);
			response = thermometerAsset.getTemp(command);
			break;

		case "GetLocationCommand":
			GPSAsset locationAsset = new GPSAsset(null);
			response = locationAsset.getLoc(command);
			break;

		case "GetPressureCommand":
			BarometerAsset barometerAsset = new BarometerAsset(null);
			response = barometerAsset.getPressure(command);
			break;

		case "MakeMoveCommand":
			DriveAsset driveAsset = new DriveAsset(null);
			response = driveAsset.getMove(command);
			break;

		case "RotateCommand":
			SteererAsset steerAsset = new SteererAsset(null);
			response = steerAsset.getRotation(command);
			break;
		}

		log(response);
		return response;

	}

	public static void prompt(String s) {
		System.out.print(s + " ");
	}

}
