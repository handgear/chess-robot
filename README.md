# Chess Robot
아두이노를 사용한 체스로봇.
크게 리모콘과 구동부로 나뉘어져있다.

#리모콘
아두이노 메가를 사용하고 있다.
CHESSuino의 코드에 블루투스를 통한 좌표입력, 구종부로 보내야하는 데이터 처리 관련된 내용을 추가하여 작성하였다.
체스 ai가 탑재되어있어 player이후 자체적인 계산 후 COM의 수를 이동시키게 된다.

#구동부
연마봉, 베어링, 각 축당 감속DC모터 1개와 수광센서 16조를 사용하였다. 여기에도 아두이노 메가를 프로세서로 사용하였다.
블루투스를 통해 리모콘으로부터 좌표를 받으며 이동완료시 완료 신호를 리모콘에 전송한다.
전자석을 이용해 말을 움직인다. 

#진행순서
리모콘으로 player가 이동시킬 좌표를 입력한다.(체스 공식 룰에서 사용하는 좌표체계 사용)
구동부가 player의 말을 움직인다.
COM이 대응되는 수를 옮긴다.
(이하 게임이 종료될 때까지 반복)

#video link
[![Chess Robot](https://raw.githubusercontent.com/handgear/chess-robot/master/thumbnail.jpg)](https://youtu.be/3UgL_F2W4Q8 "Chess Robot")
