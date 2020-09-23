package com.example;

import java.util.ArrayList;
import java.util.Scanner;

public class Party {
    private final ArrayList<Player> party = new ArrayList<>();

    public Party(boolean stdParty) {
        if (stdParty) {
            party.add(new Player("Kholwin"));
            party.add(new Player("Urimus"));
            party.add(new Player("Raith"));
            party.add(new Player("El Condor"));
            party.add(new Player("Caldazar"));
        } else {
            Scanner scanner = new Scanner(System.in);
            boolean run = true;

            // Get player list
            while (run) {
                System.out.print("Enter new player's name: ");
                String name = scanner.nextLine();
                party.add(new Player(name));

                System.out.print("Add more players? [Y/N]: ");
                String next = scanner.nextLine();
                if (next.equals("Y") || next.equals("y")) {
                    System.out.println();
                } else {
                    System.out.println();
                    run = false;
                }
            }
        }
    }

    public ArrayList<Player> get() {
        return party;
    }
}
