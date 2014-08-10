#ifndef BDTargeting_H
#define BDTargeting_H

#define X_calib	 80  		// Lazerio kampo koregavimas.
#define Y_calib	220		// Spindulis kiek imanoma statmenesnis korpuso priekinei sienelei.

#include <libusb-1.0/libusb.h>
#include <QtGui/QDialog>
#include <QDialog>
#include <QCheckBox>
#include <QTextEdit>
#include <QSpinBox>
#include <QThread> 
#include <QTest>

class BDTargeting : public QDialog
{
Q_OBJECT
public:
    BDTargeting();
    virtual ~BDTargeting();
    
    int open_device(libusb_device_handle **device, libusb_context **uctx);
    /* Funkcija open_device() pradeda libusb sesija, ir atidaro 
     * irengini pagal jo VendorID ir ProductID.
     * Kintamasis device nuoroda i irenginio handle,
     * nuoroda uctx nurodo i kintamaji ctx - informacija apie libusb sesija.
     * Funkcija privalo buti iskvesta pries siunciant duomenys su send_data() funkcija.
     * Baigiant sesija, turi but iskvesto funkcijos:  
     * libusb_close(dev_handle)- uzdarome atidaryta irengini
     * libusb_exit(ctx) - uzbaigiama libusb sesija
     */ 
    int send_data(int servo, int pos_x, int pos_y, int laser_enbl, int reset_enbl, int buzzer, libusb_device_handle *dev_handle);
    /* Funckcija siuncia duomenys i mikrovaldikli, kur kintamasis servo gali igiti viena is triju reiksmiu  
     * 1 - kai siunciami duomenys skirti nukreipti pirma nukreipimo mechanizma;
     * 2 - kai siunciami duomenys skirti nukreipti antra nukrepimo mechanizma;
     * 3- duomenys skirti papildomamam servo mechanizmui.
     * -----------------------------------------------------
     * Kintameji pos_x ir posy skirti perduoti nukreipimo duomenys pagal x ir y asi atitinkamai. 
     * Reiksme gali buti nuo 0 iki 255, skaicius  128 atitinka 90 laipsniu servo posukio kampa,
     * t.y. centrine padeti.
     * -----------------------------------------------------
     * laser_enbl kitamajam priskiriama reiksme 1, kai reikia ijungti lazeri.
     * -----------------------------------------------------
     * Jeigu reset_enbl reiksme bus 1, irenginis, per 3 sekundes negaves jokiu duomenu is 
     * kompiuteriaus, persikraus.
     * Del neaiskiu priezasciu mikrovaldiklio V_USB tvarkikle gali nustuoti reaguoti i iskveciamas
     * pertrauktis pagal D+ linijos lygi ant PD2 isvado. Priverstinis perkrovimas leidzia grazinti
     * irengini sistemai.
     * Jeigu perkrovimas nereikalingas reset_enbl = 0.
     * -----------------------------------------------------
     * buzzer gali buti: 0 - nera garsinio signalo; 1 - objekto aptikimo signalas; 2 - objekto praradimo signalas; 
     * trecio tipo signalas (saudimas i objekta) priklauso nuo lazerio signalo. 
     */
    int set_config(int config);
    /* Irenginio konfiguravimas.
     * 
     */

private:
    
    QCheckBox *Servo1_checkbox;
    QCheckBox *Servo2_checkbox;
    QCheckBox *addServo_checkbox;
    QCheckBox *Supply_checkbox; 
    QCheckBox *Laser_3V_checkbox;
    QCheckBox *Laser_5V_checkbox;
    QCheckBox *Buzzer_checkbox;
 
    QTextEdit *smallEditor;
    QCheckBox *Laser_checkbox;
    QSpinBox *spinbox1;
    QSpinBox *spinbox2;

public slots:    
    void check_config();
    void DATA_SEND_EXAMPLE();
    void DATA_SEND_EXAMPLE_2();
    void DATA_SEND_EXAMPLE_3();
    void test_device();
    

};

class Thread : public QThread
{
public:
    static void msleep(int ms)
    {
        QThread::msleep(ms);
    }
};


#endif // BDTargeting_H
