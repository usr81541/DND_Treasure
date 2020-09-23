package com.example;

public class Purse {
    private int platinum,
                gold,
                electrum,
                silver,
                copper;

    public void displayContents() {
        System.out.println("Purse contents:");
        System.out.println("Platinum: " + platinum);
        System.out.println("Gold: " + gold);
        System.out.println("Electrum: " + electrum);
        System.out.println("Silver: " + silver);
        System.out.println("Copper: " + copper + "\n");
    }

    public void displayTotalGold() {
        int     totalGold = gold,
                totalElectrum = electrum,
                totalSilver = silver,
                totalCopper = copper;

        totalSilver += totalCopper / 10;
        totalCopper %= 10;
        totalElectrum += totalSilver / 5;
        totalSilver %= 5;
        totalGold += totalElectrum / 2;
        totalElectrum %= 2;
        totalGold += platinum * 10;

        System.out.println("The total value in gold is:\n" +
                totalGold + "gp " +
                totalElectrum + "ep " +
                totalSilver + "sp " +
                totalCopper + "cp");
    }

    public Purse(int platinum, int gold, int electrum, int silver, int copper) {
        this.platinum = platinum;
        this.gold = gold;
        this.electrum = electrum;
        this.silver = silver;
        this.copper = copper;
    }

    public Purse() {
        this.platinum = 0;
        this.gold = 0;
        this.electrum = 0;
        this.silver = 0;
        this.copper = 0;
    }

    public int getPlatinum() {
        return platinum;
    }

    public void setPlatinum(int platinum) {
        this.platinum = platinum;
    }

    public int getGold() {
        return gold;
    }

    public void setGold(int gold) {
        this.gold = gold;
    }

    public int getElectrum() {
        return electrum;
    }

    public void setElectrum(int electrum) {
        this.electrum = electrum;
    }

    public int getSilver() {
        return silver;
    }

    public void setSilver(int silver) {
        this.silver = silver;
    }

    public int getCopper() {
        return copper;
    }

    public void setCopper(int copper) {
        this.copper = copper;
    }

    public void addPlatinum(int platinum) {
        this.platinum += platinum;
    }

    public void addGold(int gold) {
        this.gold += gold;
    }

    public void addElectrum(int electrum) {
        this.electrum += electrum;
    }

    public void addSilver(int silver) {
        this.silver += silver;
    }

    public void addCopper(int copper) {
        this.copper += copper;
    }

    public void subtractPlatinum(int platinum) {
        this.platinum -= platinum;
    }

    public void subtractGold(int gold) {
        this.gold -= gold;
    }

    public void subtractElectrum(int electrum) {
        this.electrum -= electrum;
    }

    public void subtractSilver(int silver) {
        this.silver -= silver;
    }

    public void subtractCopper(int copper) {
        this.copper -= copper;
    }

}
