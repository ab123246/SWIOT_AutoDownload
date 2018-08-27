@echo off 
cd C:\Users\ab123\Desktop\platform-tools
@echo 1.配對後確認音樂是否可正常播放(是否有雜音或斷斷續續)
pause>nul
@echo 2.使用DUT與耳機調整音樂大小聲/暫停播放/上一首下一首(如果耳機無按鍵可調整請用手機)
pause>nul
@echo 3.將音樂暫停把DUT調整鈴響模式，使用按鍵撥號時耳機要有按鍵音(測完請將手機調回靜音，並且繼續播放音樂)
pause>nul
@echo 4.使用耳機重播上一通電話(Plantronic voyager Edge、Uclear HBC200此兩款設備要先將音樂暫停才能重播)
pause>nul
@echo 5.從REF機打電話給測試機，使用耳機拒接電話
pause>nul
@echo 6.將手機重新開機(開機後請確認功能一樣要正常一樣要播音樂)
pause>nul
@echo 7.打一通電話給DUT並用藍牙耳機接聽並持續通話3分鐘(通話時請用手機跟耳機調整音量大小確認能正常調整音量)
adb shell input keyevent 5
pause>nul