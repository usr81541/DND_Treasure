package com.example;

import java.util.ArrayList;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        Purse commonPurse = new Purse();
        Party party;
        String input;
        Scanner scanner = new Scanner(System.in);

        System.out.print("Custom Party? [Y/N]:\t");
        input = scanner.nextLine();
        if (input.equals("Y") || input.equals("y")) {
            party = new Party(false);
        } else {
            party = new Party(true);
        }

        System.out.println("Enter common purse value:");
        commonPurse.setPlatinum(getTreasure("Platinum"));
        commonPurse.setGold(getTreasure("Gold"));
        commonPurse.setElectrum(getTreasure("Electrum"));
        commonPurse.setSilver(getTreasure("Silver"));
        commonPurse.setCopper(getTreasure("Copper"));

        System.out.println("\nCommon Purse (full):");
        commonPurse.displayContents();

        dividePurse(party.get(), commonPurse);

        for (Player p : party.get()) {
            System.out.println("Player: " + p.getName());
            p.displayContents();
            p.displayTotalGold();
            System.out.println();
        }

        System.out.println("Common Purse (emptied):");
        commonPurse.displayContents();

        System.out.print("Press ENTER to close...");
        scanner.nextLine();
    }

    private static int getTreasure(String request) {
        Scanner scanner = new Scanner(System.in);

        while (true) {
            System.out.print(request + ": ");
            if (scanner.hasNextInt()) {
                return scanner.nextInt();
            } else {
                System.out.println("Enter an integer");
            }
            scanner.nextLine();
        }
    }

    private static void dividePurse(ArrayList<Player> players, Purse commonPurse) {

        parseCoins(players, commonPurse, Coin.PLATINUM);
        parseCoins(players, commonPurse, Coin.GOLD);
        parseCoins(players, commonPurse, Coin.ELECTRUM);
        parseCoins(players, commonPurse, Coin.SILVER);
        parseCoins(players, commonPurse, Coin.COPPER);

    }

    private static void parseCoins(ArrayList<Player> players, Purse purse, Coin coin) {
        int limit;

        switch (coin) {
            case PLATINUM:
                // Give each player some platinum
                for (Player p : players) {
                    p.addPlatinum(purse.getPlatinum() / players.size());
                }

                // Adjust purse platinum quantity
                purse.setPlatinum(purse.getPlatinum() % players.size());

                // Distribute remaining platinum if possible
                // If there's enough platinum to make it worth it (more than half the party size)
                // and if there's enough gold to actually backfill the platinum:
                if ((purse.getPlatinum() > players.size() / 2) &&
                        (purse.getGold() >= (players.size() - purse.getPlatinum()) * 10)) {

                    //Give out the remaining platinum
                    limit = purse.getPlatinum();
                    for (int i = 0; i < limit; i++) {
                        players.get(i).addPlatinum(1);
                        purse.subtractPlatinum(1);
                    }   // at the end of this loop, purse.platinum should equal zero

                    // Give out 10 gold to each remaining player for the missing platinum
                    for (int i = limit; i < players.size(); i++) {
                        players.get(i).addGold(10);
                        purse.subtractGold(10);
                    }
                }
                break;
            case GOLD:
                // Give each player some gold
                for (Player p : players) {
                    p.addGold(purse.getGold() / players.size());
                }

                // Adjust purse gold quantity
                purse.setGold(purse.getGold() % players.size());

                // Distribute remaining gold if possible
                // If there's enough gold to make it worth it (more than half the party size)
                // and if there's enough electrum or silver to actually backfill the gold:
                if (purse.getGold() > players.size() / 2) {
                    if ((purse.getElectrum() >= (players.size() - purse.getGold()) * 2)) {

                        // Give out remaining gold
                        limit = purse.getGold();
                        for (int i = 0; i < limit; i++) {
                            players.get(i).addGold(1);
                            purse.subtractGold(1);
                        }   // at the end of this loop purse.gold should equal 0

                        // Give out 2 electrum to each remaining player for the missing gold
                        for (int i = limit; i < players.size(); i++) {
                            players.get(i).addElectrum(2);
                            purse.subtractElectrum(2);
                        }
                    } else if (purse.getSilver() >= (players.size() - purse.getGold()) * 10) {

                        // Give out remaining gold
                        limit = purse.getGold();
                        for (int i = 0; i < limit; i++) {
                            players.get(i).addGold(1);
                            purse.subtractGold(1);
                        }

                        // Give out 10 silver to each remaining player for the missing gold
                        for (int i = limit; i < players.size(); i++) {
                            players.get(i).addSilver(10);
                            purse.subtractSilver(10);
                        }
                    }
                }
                break;
            case ELECTRUM:
                // Give each player some electrum
                for (Player p : players) {
                    p.addElectrum(purse.getElectrum() / players.size());
                }

                // Adjust purse electrum quantity
                purse.setElectrum(purse.getElectrum() % players.size());

                // Distribute remaining electrum if possible
                // If there's enough electrum to make it worth it (more than half the party size)
                // and if there's enough silver to actually backfill the electrum:
                if ((purse.getElectrum() > players.size() / 2) &&
                        (purse.getSilver() >= (players.size() - purse.getElectrum()) * 5)) {

                    // Give out the remaining electrum
                    limit = purse.getElectrum();
                    for (int i = 0; i < limit; i++) {
                        players.get(i).addElectrum(1);
                        purse.subtractElectrum(1);
                    }   // at the end of this loop purse.electrum should equal 0

                    // Give out 5 silver to each remaining player for the missing electrum
                    for (int i = limit; i < players.size(); i++) {
                        players.get(i).addSilver(5);
                        purse.subtractSilver(5);
                    }
                }
                break;
            case SILVER:
                // Give each player some silver
                for (Player p : players) {
                    p.addSilver(purse.getSilver() / players.size());
                }

                // Adjust purse silver quantity
                purse.setSilver(purse.getSilver() % players.size());

                // Distribute remaining silver if possible
                // If there's enough silver to make it worth it (more than half the party size)
                // and if there's enough copper to actually backfill the silver:
                if ((purse.getSilver() > players.size() / 2) &&
                        (purse.getCopper() >= (players.size() - purse.getSilver()) * 10)) {

                    // Give out the remaining silver
                    limit = purse.getSilver();
                    for (int i = 0; i < limit; i++) {
                        players.get(i).addSilver(1);
                        purse.subtractSilver(1);
                    }   // at the end of this loop purse.silver should equal 0

                    // Give out 10 copper to each remaining player for the missing silver
                    for (int i = limit; i < players.size(); i++) {
                        players.get(i).addCopper(10);
                        purse.subtractCopper(10);
                    }
                }
                break;
            case COPPER:
                // Give each player some copper
                for (Player p : players) {
                    p.addCopper(purse.getCopper() / players.size());
                }

                // Adjust purse copper quantity
                purse.setCopper(purse.getCopper() % players.size());
        }
    }
}
