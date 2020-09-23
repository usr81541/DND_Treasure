package com.example;

public class Player extends Purse{
    private final String name;

    public Player(String name, int platinum, int gold, int electrum, int silver, int copper) {
        super(platinum, gold, electrum, silver, copper);
        this.name = name;
    }

    public Player(String name) {
        super();
        this.name = name;
    }

    public String getName() {
        return name;
    }
}
