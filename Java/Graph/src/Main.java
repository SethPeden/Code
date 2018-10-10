import javax.swing.*;
import java.awt.*;

public class Main {
	public static void main(String[] args) {
		int screenWidth = Toolkit.getDefaultToolkit().getScreenSize().width;
		int screenHeight = Toolkit.getDefaultToolkit().getScreenSize().height;
		int width = 2 * screenWidth / 3, height = 2 * screenHeight / 3;
		JFrame frame = new JFrame("Test");
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setSize(new Dimension(width, height));
		frame.setLocation((screenWidth - width) / 2, (screenHeight - height) / 2);
		frame.setVisible(true);
	}
}