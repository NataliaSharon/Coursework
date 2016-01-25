public abstract class Asset {
	protected String name;

	public Asset(String name) {
		this.name = name;
	}

	public String getName() {
		return name;
	}

	public Response execute(Command command) {

	}
	
	
	
}
