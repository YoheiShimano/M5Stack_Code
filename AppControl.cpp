#include "AppControl.h"
#include <Arduino.h>
#include <M5Stack.h>

MdLcd mlcd;
MdWBGTMonitor mwbgt;
MdMusicPlayer mmplay;
MdMeasureDistance mmdist;
MdDateTime mdtime;

const char* g_str_orange[] = {
    COMMON_ORANGE0_IMG_PATH,
    COMMON_ORANGE1_IMG_PATH,
    COMMON_ORANGE2_IMG_PATH,
    COMMON_ORANGE3_IMG_PATH,
    COMMON_ORANGE4_IMG_PATH,
    COMMON_ORANGE5_IMG_PATH,
    COMMON_ORANGE6_IMG_PATH,
    COMMON_ORANGE7_IMG_PATH,
    COMMON_ORANGE8_IMG_PATH,
    COMMON_ORANGE9_IMG_PATH,
};

const char* g_str_blue[] = {
    COMMON_BLUE0_IMG_PATH,
    COMMON_BLUE1_IMG_PATH,
    COMMON_BLUE2_IMG_PATH,
    COMMON_BLUE3_IMG_PATH,
    COMMON_BLUE4_IMG_PATH,
    COMMON_BLUE5_IMG_PATH,
    COMMON_BLUE6_IMG_PATH,
    COMMON_BLUE7_IMG_PATH,
    COMMON_BLUE8_IMG_PATH,
    COMMON_BLUE9_IMG_PATH,
};

void AppControl::setBtnAFlg(bool flg)
{
    m_flag_btnA_is_pressed = flg;
}

void AppControl::setBtnBFlg(bool flg)
{
    m_flag_btnB_is_pressed = flg;
}

void AppControl::setBtnCFlg(bool flg)
{
    m_flag_btnC_is_pressed = flg;
}

void AppControl::setBtnAllFlgFalse()
{
    m_flag_btnA_is_pressed = false;
    m_flag_btnB_is_pressed = false;
    m_flag_btnC_is_pressed = false;
}

State AppControl::getState()
{
    return m_state;
}

void AppControl::setState(State state)
{
    m_state = state;
}

Action AppControl::getAction()
{
    return m_action;
}

void AppControl::setAction(Action action)
{
    m_action = action;
}

void AppControl::setStateAction(State state, Action action)
{
    setState(state);
    setAction(action);
}

FocusState AppControl::getFocusState()//フォーカスのステータスを取得
{
    return m_focus_state;
}

void AppControl::setFocusState(FocusState fs)//フォーカスのステータスをセット
{
    m_focus_state = fs;
}

void AppControl::displayTitleInit()//タイトルを表示するための関数
{
    mlcd.displayJpgImage(TITLE_IMG_PATH );
}

void AppControl::displayMenuInit()//メニュー画面を表示
{
    mlcd.displayJpgImageCoordinate(MENU_WBGT_IMG_PATH, 0, 0);//熱中症モニタ画像
    mlcd.displayJpgImageCoordinate(MENU_MUSIC_IMG_PATH, 0, 50);//音楽プレイヤー画像
    mlcd.displayJpgImageCoordinate(MENU_MEASURE_IMG_PATH, 0, 100);//距離測定画像
    mlcd.displayJpgImageCoordinate(MENU_DATE_IMG_PATH, 0, 150);//時刻表示画像
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_UP_IMG_PATH, 0, 200);//上矢印画像
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_DECIDE_IMG_PATH, 120, 200);//決定画像
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_DOWN_IMG_PATH, 240, 200);//下矢印画像
    setFocusState(MENU_WBGT);
    mlcd.displayJpgImageCoordinate(MENU_WBGT_FOCUS_IMG_PATH, 0, 0);
}

void AppControl::focusChangeImg(FocusState current_state, FocusState next_state)//フォーカス
{
    if(current_state == MENU_WBGT){
        mlcd.displayJpgImageCoordinate(MENU_WBGT_IMG_PATH, 0, 0);
    }else if(current_state == MENU_MUSIC){
        mlcd.displayJpgImageCoordinate(MENU_MUSIC_IMG_PATH, 0, 50);
    }else if(current_state == MENU_MEASURE){
        mlcd.displayJpgImageCoordinate(MENU_MEASURE_IMG_PATH, 0, 100);
    }else if(current_state == MENU_DATE){
        mlcd.displayJpgImageCoordinate(MENU_DATE_IMG_PATH, 0, 150);
    }

    if(next_state == MENU_WBGT){
        mlcd.displayJpgImageCoordinate(MENU_WBGT_FOCUS_IMG_PATH, 0, 0);
    }else if(next_state == MENU_MUSIC){
        mlcd.displayJpgImageCoordinate(MENU_MUSIC_FOCUS_IMG_PATH, 0, 50);
    }else if(next_state == MENU_MEASURE){
        mlcd.displayJpgImageCoordinate(MENU_MEASURE_FOCUS_IMG_PATH, 0, 100);
    }else if(next_state == MENU_DATE){
        mlcd.displayJpgImageCoordinate(MENU_DATE_FOCUS_IMG_PATH, 0, 150);
    }
}

void AppControl::displayWBGTInit(){ //熱中症モニタ
    mlcd.displayJpgImageCoordinate(WBGT_TEMPERATURE_IMG_PATH, 0,0); //温度の座標
    mlcd.displayJpgImageCoordinate(g_str_orange[(temperature / 10) % 10], 120, 0); //温度10の位
    mlcd.displayJpgImageCoordinate(g_str_orange[temperature % 10], 153 , 0); //温度1の位
    mlcd.displayJpgImageCoordinate(COMMON_ORANGEDOT_IMG_PATH, 186, 0); //ドット
    mlcd.displayJpgImageCoordinate(g_str_orange[0], 220, 0); //小数点
    mlcd.displayJpgImageCoordinate(WBGT_PERCENT_IMG_PATH, 96, 100);//「%」

    mlcd.displayJpgImageCoordinate(WBGT_HUMIDITY_IMG_PATH, 0, 50); //湿度の座標
    mlcd.displayJpgImageCoordinate(g_str_blue[(humidity / 10) % 10], 120, 50); // 湿度10の位
    mlcd.displayJpgImageCoordinate(g_str_blue[humidity % 10], 153, 50); //湿度1の位
    mlcd.displayJpgImageCoordinate(COMMON_ORANGEDOT_IMG_PATH, 186, 50); //ドット
    mlcd.displayJpgImageCoordinate(g_str_blue[0], 220, 50);// 少数点
    mlcd.displayJpgImageCoordinate(WBGT_DEGREE_IMG_PATH, 253, 50);//「℃」

    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_BACK_IMG_PATH, 120, 200);//戻る画像
}

void AppControl::displayTempHumiIndex(){

    mlcd.displayJpgImageCoordinate(WBGT_SAFE_IMG_PATH, 0, 100);//安全
    mlcd.displayJpgImageCoordinate(WBGT_ATTENTION_IMG_PATH, 0, 100);//注意
    mlcd.displayJpgImageCoordinate(WBGT_ALERT_IMG_PATH, 0, 100);//警戒
    mlcd.displayJpgImageCoordinate(WBGT_HIGH_ALERT_IMG_PATH, 0, 100);//厳重警戒
    mlcd.displayJpgImageCoordinate(WBGT_DANGER_IMG_PATH, 0, 100);//危険
}

void AppControl::displayMusicInit(){//音楽プレイヤー押下時に表示
    mmplay.init();
    mlcd.displayJpgImageCoordinate(MUSIC_NOWSTOPPING_IMG_PATH, 0, 0);
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_PLAY_IMG_PATH, 0, 200);
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_BACK_IMG_PATH, 120, 200);
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_NEXT_IMG_PATH, 240, 200);
}

void AppControl::displayMusicStop(){//音楽プレイヤー 音楽停止時に表示
    mlcd.displayJpgImageCoordinate(MUSIC_NOWSTOPPING_IMG_PATH, 0, 0);
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_PLAY_IMG_PATH, 0, 200);
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_BACK_IMG_PATH, 120, 200);
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_NEXT_IMG_PATH, 240, 200);
}

void AppControl::displayMusicTitle(){//現在の曲のタイトルを表示
    mlcd.displayText(mmplay.getTitle(), 10, 120);
}

void AppControl::displayNextMusic(){//次の音楽のタイトルを表示
    mmplay.selectNextMusic();
    mlcd.displayText(mmplay.getTitle(), 10, 120);
}

void AppControl::displayMusicPlay(){//音楽再生時に表示
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_FILLWHITE_IMG_PATH, 10, 120);
    mlcd.displayJpgImageCoordinate(MUSIC_NOWPLAYING_IMG_PATH, 0, 0);
    mlcd.displayText(mmplay.getTitle(), 10, 120);
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_STOP_IMG_PATH, 0, 200);
}

void AppControl::displayMeasureInit(){//距離測定画面の表示
    mlcd.displayJpgImageCoordinate(MEASURE_NOTICE_IMG_PATH, 0, 0);
    mlcd.displayJpgImageCoordinate(MEASURE_CM_IMG_PATH, 240,100);
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_BACK_IMG_PATH, 120, 200);
}

void AppControl::displayMeasureDistance(){//距離測定の関数
    double distance = mmdist.getDistance();

    if (int(distance) >= 100) {
        mlcd.displayJpgImageCoordinate(g_str_blue[(int(distance) / 100) % 10], 10, 100); //distanceの値　÷　100, 割った余りを百の位に表示 
    } else {
        mlcd.displayJpgImageCoordinate(COMMON_BLUEFILLWHITE_IMG_PATH, 10, 100); //distanceの値が100未満なら百の位を隠す
    }

    if (int(distance) >= 10) {
        mlcd.displayJpgImageCoordinate(g_str_blue[(int(distance) / 10) % 10], 53, 100);
    } else {
        mlcd.displayJpgImageCoordinate(COMMON_BLUEFILLWHITE_IMG_PATH, 53, 100);
    }
    
    mlcd.displayJpgImageCoordinate(g_str_blue[int(distance) % 10], 96, 100);
    mlcd.displayJpgImageCoordinate(COMMON_BLUEDOT_IMG_PATH, 139, 100);
    mlcd.displayJpgImageCoordinate(g_str_blue[int(distance * 10) % 10], 182, 100);
}

void AppControl::displayDateInit(){//DATEモードの画面表示
    mlcd.displayJpgImageCoordinate(DATE_NOTICE_IMG_PATH, 0, 0);
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_BACK_IMG_PATH, 120, 200);

}

void AppControl::displayDateUpdate(){
    mdtime.readDate();
    mdtime.readTime();
}

void AppControl::controlApplication(){
    while (1) {

        switch (getState()) {
        case TITLE://タイトル画面
            switch (getAction()) {
            case ENTRY:
                /*
                ** まずはここにタイトル画面の表示処理を呼び出してみよう。
                ** タイトル画面表示の関数はdisplayTitleInit()である。
                ** この関数の中身はまだ何もないので、この関数にタイトル画面表示処理を書いてみよう。
                */
                mmplay.init();
                displayTitleInit();
                setStateAction(TITLE, DO);
                break;

            case DO:
                if(m_flag_btnA_is_pressed || m_flag_btnB_is_pressed ||m_flag_btnC_is_pressed){
                setBtnAllFlgFalse();
                setStateAction(TITLE, EXIT);
                }
                break;

            case EXIT:
                setStateAction(MENU, ENTRY);
                break;

            default:
                break;
            }

            break;

        case MENU://メニュー画面
            switch (getAction()) {
            case ENTRY://メニュー画面の表示
                mlcd.clearDisplay();
                displayMenuInit();
                setStateAction(MENU, DO);
                break;

            case DO:
            if (m_flag_btnA_is_pressed) {//ボタンA(↑)押下時ケースが上に移行
                
                switch (getFocusState()) {
                    case MENU_WBGT:
                    setBtnAllFlgFalse();
                    focusChangeImg(MENU_WBGT, MENU_DATE);
                    setFocusState(MENU_DATE);   
                    break;

                    case MENU_MUSIC:
                    setBtnAllFlgFalse();
                    focusChangeImg(MENU_MUSIC, MENU_WBGT);
                    setFocusState(MENU_WBGT);
                    break;

                    case MENU_MEASURE:
                    setBtnAllFlgFalse();
                    focusChangeImg(MENU_MEASURE, MENU_MUSIC);
                    setFocusState(MENU_MUSIC);
                    break;

                    case MENU_DATE:
                    setBtnAllFlgFalse();
                    focusChangeImg(MENU_DATE, MENU_MEASURE);
                    setFocusState(MENU_MEASURE);
                    break;

                    default:
                    break;
                }
                setBtnAllFlgFalse();
            } else if (m_flag_btnC_is_pressed) {//ボタンC(↓)押下時ケースが下に移行
                setBtnAllFlgFalse();

                switch (getFocusState()) {
                    case MENU_WBGT:
                    setBtnAllFlgFalse();
                    focusChangeImg(MENU_WBGT, MENU_MUSIC);
                    setFocusState(MENU_MUSIC);
                    break;

                    case MENU_MUSIC:
                    setBtnAllFlgFalse();
                    focusChangeImg(MENU_MUSIC, MENU_MEASURE);
                    setFocusState(MENU_MEASURE);
                    break;

                    case MENU_MEASURE:
                    setBtnAllFlgFalse();
                    focusChangeImg(MENU_MEASURE, MENU_DATE);
                    setFocusState(MENU_DATE);
                    break;

                    case MENU_DATE:
                    setBtnAllFlgFalse();
                    focusChangeImg(MENU_DATE, MENU_WBGT);
                    setFocusState(MENU_WBGT);
                    break;
                    
                    default:
                    break;
                }
            } else if (m_flag_btnB_is_pressed) {//ボタンB(決定)押下時、各種モードに移行
                setBtnAllFlgFalse();
                setStateAction(MENU,EXIT);
            }
            break;

            case EXIT:
                switch (getFocusState()) {
                    case MENU_WBGT:
                    setStateAction(WBGT, ENTRY);
                    break;
                    
                    case MENU_MUSIC:
                    setStateAction(MUSIC_STOP, ENTRY);
                    break;
                    
                    case MENU_MEASURE:
                    setStateAction(MEASURE, ENTRY);
                    break;
                    
                    case MENU_DATE:
                    setStateAction(DATE, ENTRY);
                    break;
                    
                    default:
                    break;
                }
                break;
            }
            break;

        case WBGT://熱中症測定

            switch (getAction()) {
            case ENTRY:
                setBtnAllFlgFalse();//ボタンをfalseに
                mlcd.fillBackgroundWhite();
                displayWBGTInit();//画面表示
                displayTempHumiIndex();//温湿度によって画像切り替え
                setStateAction(WBGT,DO);
                break;

            case DO:
                delay(100);
                displayTempHumiIndex();//温湿度によって画像切り替え
                break;

            case EXIT:
                break;

            default:
                break;
            }
            break;

        case MUSIC_STOP://音楽再生＿停止
            switch (getAction()) {
            case ENTRY:
                setBtnAllFlgFalse();
                mlcd.fillBackgroundWhite();
                displayMusicInit();
                displayMusicTitle();
                setStateAction(MUSIC_STOP,DO);
                break;

            case DO:
                if(m_flag_btnA_is_pressed) {//A(再生)ボタンが押されたら
                    setStateAction(MUSIC_STOP, EXIT);
                }else if(m_flag_btnB_is_pressed) {//B(戻る)ボタンが押されたら
                    setStateAction(MUSIC_STOP, EXIT);
                }else if(m_flag_btnC_is_pressed) {//C(次の曲)ボタンが押されたら
                    displayNextMusic();
                    setBtnAllFlgFalse();
                }
                break;
                
            case EXIT:
                if(m_flag_btnA_is_pressed){ //A(再生)ボタンが押されている状態なら
                    setStateAction(MUSIC_PLAY, ENTRY);
                }else {
                    setStateAction(MENU, ENTRY);
                }
                setBtnAllFlgFalse();
                break;
            }
            break;

        case MUSIC_PLAY://音楽再生

            switch (getAction()) {
            case ENTRY:
                setBtnAllFlgFalse();
                mlcd.fillBackgroundWhite();
                mmplay.prepareMP3();//音楽ファイルの再生に必要なインスタンスの生成とデコードを開始する
                mmplay.playMP3();//音楽を再生 
                displayMusicTitle();
                setStateAction(MUSIC_PLAY, DO);
                break;

            case DO:
                displayMusicPlay();
                while (mmplay.isRunningMP3()) {
                    if (!mmplay.playMP3() || m_flag_btnA_is_pressed) {//音楽の再生が止まっている　or　A(停止)ボタンが押下されたら再生を止める
                        mmplay.stopMP3();
                        setStateAction(MUSIC_PLAY, EXIT);
                        setBtnAllFlgFalse();
                    }
                }
            break;

            case EXIT:
                setBtnAllFlgFalse();
                setStateAction(MUSIC_STOP, ENTRY);
                break;
            }
            break;

        case MEASURE://距離測定

            switch (getAction()) {
            case ENTRY:
                setBtnAllFlgFalse();
                mlcd.fillBackgroundWhite();
                displayMeasureInit();
                displayMeasureDistance();
                setStateAction(MEASURE,DO);
                break;

            case DO:
                setBtnAllFlgFalse();
                displayMeasureDistance();
                delay(250);
                if(m_flag_btnB_is_pressed) {
                setStateAction(MEASURE, EXIT);
                }
                break;

            case EXIT:
                setBtnAllFlgFalse();
                setStateAction(MENU, ENTRY);
                break;
            }
            break;

        case DATE://日付と時刻の表示

            switch (getAction()) {
            case ENTRY:
                setBtnAllFlgFalse();
                mlcd.fillBackgroundWhite();
                displayDateInit();
                setStateAction(DATE,DO);
                break;

            case DO: {
                setBtnAllFlgFalse();
                
                String date = mdtime.readDate();
                String time = mdtime.readTime();

                mlcd.displayDateText(date, 10, 100);
                mlcd.displayDateText(time, 40 , 150);

                if(m_flag_btnB_is_pressed) {
                setStateAction(DATE, EXIT);
                }
                break;
            }
            break;
            case EXIT:
                setBtnAllFlgFalse();
                setStateAction(MENU, ENTRY);
                break;
            }
            break;
        }
    }
}