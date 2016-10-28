int(m_vecTile[iIndex]->fX + m_fScrollX) < 0 &&	// 메이플 브금 사이트


/// 스테이지별로 TILEX, TILEY 구해주기

/// 인덱스로 타일 X,Y좌표 구하기.
x = INDEX - (y * TILEX);
x = (FCX / 2) + (x * TILEFCX); 

y = INDEX / TILEX;
y = (FCY / 2) + (y * TILEFCY);