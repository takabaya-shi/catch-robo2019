/*
 * autoctrl.c
 *
 *  Created on: 2019/08/17
 *      Author: tomok
 */


/*
 * 直交座標を円筒座標に変換
 * @param	*rec_points, *cyl_points : それぞれ直交座標、円筒座標
 * @return
 * @note	ポインタ渡し変数に代入
 */
/*
void Rec2Cyl(struct_rec *rec_point, struct_cyl *cyl_point) {
	//r座標
	float r = sqrtf(powf(rec_point->x, 2) + powf(rec_point->y, 2));

	//theta座標
	float theta = atan2f(rec_point->y, rec_point->x);

	*/
/*
	if (rec_point->x < 0 && rec_point->y < 0) {	//第四象限の時
		theta = 2 * M_PI + theta;
	}
*/
	//それぞれ代入
/*
	cyl_point->r     = r;
	cyl_point->theta = theta;
	cyl_point->z = rec_point->z;
}

void Cyl2Rec(struct_cyl *cyl_point, struct_rec *rec_point) {
	rec_point->x = cyl_point->r * cosf(cyl_point->theta);
	rec_point->y = cyl_point->r * sinf(cyl_point->theta);
	rec_point->z = cyl_point->z;
}

*/
