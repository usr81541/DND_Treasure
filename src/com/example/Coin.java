package com.example;

public enum Coin {
    PLATINUM(0),
    GOLD(1),
    ELECTRUM(2),
    SILVER(3),
    COPPER(4);

    private final int coin;

    Coin(int coin) {
        this.coin = coin;
    }

    public int value() {
        return this.coin;
    }
}
