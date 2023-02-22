import java.awt.BorderLayout;
import javax.swing.*; 
import java.awt.event.*;
import java.io.BufferedReader;
import java.io.InputStreamReader; 
import java.io.*;
import java.net.*;

public class Fenetre extends JFrame implements ActionListener {
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	JButton button1;
	JButton button2;
	JButton button3;
	JTextArea textArea;
	JPanel panel;
	JScrollPane scrollPane;
	JMenuBar menuBar;
	JMenu menu;
	JMenuItem menuItem1;
	JMenuItem menuItem2;
	JMenuItem menuItem3;
	JToolBar toolbar;
	JButton button_tb1;
	JButton button_tb2;
	JButton button_tb3;
	JButton test;
	
	 //Variables for the client
    static final String DEFAULT_HOST = "localhost";
    static final int DEFAULT_PORT = 3331;
    static Client client;
	
	public static void main(String argv[ ]) {
		new Fenetre();
		
		String host = DEFAULT_HOST;
	    int port = DEFAULT_PORT;
	    if (argv.length >=1) host = argv[0];
	    if (argv.length >=2) port = Integer.parseInt(argv[1]);
	    
	    //Client client = null;
	    
	    try {
	      client = new Client(host, port);
	    }
	    catch (Exception e) {
	      System.err.println("Client: Couldn't connect to "+host+":"+port);
	      System.exit(1);
	    }	    
	    
	    System.out.println("Client connected to "+host+":"+port);
	}
	
	public Fenetre() 
	{
		JToolBar toolBar = new JToolBar();
		button_tb1 = new JButton("Play");
		button_tb2 = new JButton("Search");
		button_tb3 = new JButton("Quit");
		button_tb1.addActionListener(this);
		button_tb2.addActionListener(this);
		button_tb3.addActionListener(this);
		toolBar.add(button_tb1);
		toolBar.add(button_tb2);
		toolBar.add(button_tb3);

		JMenuBar menuBar = new JMenuBar();
	    JMenu menu = new JMenu("Menu");
	    JButton test = new JButton("Test");
	    JMenuItem menuItem1 = new JMenuItem("Play");
	    JMenuItem menuItem2 = new JMenuItem("Search");
	    JMenuItem menuItem3 = new JMenuItem("Quit"); 
	    menuItem1.addActionListener(this);
	    menuItem2.addActionListener(this);
	    menuItem3.addActionListener(this);
	    menu.addActionListener(this);
	    menu.add(test);
	    menu.add(menuItem1);
	    menu.add(menuItem2);
	    menu.add(menuItem3);
	    menuBar.add(menu);
	    
		button1 = new JButton("Play");
		button2 = new JButton("Search");
		button3 = new JButton("Quit");
		
		button1.addActionListener(this);
		button2.addActionListener(this);
		button3.addActionListener(this);
		
		textArea = new JTextArea("Bienvenue sur votre télécommande !", 20, 30);
		scrollPane = new JScrollPane(textArea);
		
		panel = new JPanel();
		panel.add(button1);
		panel.add(button2);
		panel.add(button3);
		
		add(scrollPane, BorderLayout.CENTER);
		add(panel, BorderLayout.SOUTH);
		add(toolBar, BorderLayout.NORTH);
		
		setJMenuBar(menuBar);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setTitle("Telecommande");
		pack(); // calcule la disposition spatiale 
		setVisible(true); // rend l’interface visible 	
	}
	
	public void actionPerformed(ActionEvent e) {
		
		// Requête Play
		if (e.getSource() == button1 || e.getSource() == button_tb1 || e.getSource() == menuItem1) {
			// On sauvegarde le texte qui était dans la textArea
			String previous_text = textArea.getText();
			String name_object = JOptionPane.showInputDialog(null, "Name of the multimedia to play", "Input", JOptionPane.QUESTION_MESSAGE);
			// requête au serveur et récupération de la réponse + affichage sur le textArea
			try {
				String response = client.send("Play " + name_object);
                textArea.setText(previous_text + "Play " + name_object + "\n" + response + "\n");
            } catch (Exception err) {
                System.err.println("Client: IO error");
            }
		}
			
		// Requête Search
		else if (e.getSource() == button2 || e.getSource() == button_tb2 || e.getSource() == menuItem2) 
		{
			
			String previous_text = textArea.getText();
			String category_and_name = JOptionPane.showInputDialog(null, "'Multimedia'/'Group' + name", "Input", JOptionPane.QUESTION_MESSAGE);
	   
			try {
				String response = client.send("Search " + category_and_name);
				textArea.setText(previous_text + "Search " + category_and_name + "\n" + response + "\n");
            } catch (Exception err) {
                System.err.println("Client: IO error");
            }
		}
		
		else if(e.getSource() == button3 || e.getSource() == button_tb3 || e.getSource() == menuItem3)
			System.exit(0);
	}
	
}
