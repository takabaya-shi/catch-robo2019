/*
 * autoctrl.c
 *
 *  Created on: 2019/08/17
 *      Author: tomok
 */


/*
 * �������W���~�����W�ɕϊ�
 * @param	*rec_points, *cyl_points : ���ꂼ�꒼�����W�A�~�����W
 * @return
 * @note	�|�C���^�n���ϐ��ɑ��
 */
/*
void Rec2Cyl(struct_rec *rec_point, struct_cyl *cyl_point) {
	//r���W
	float r = sqrtf(powf(rec_point->x, 2) + powf(rec_point->y, 2));

	//theta���W
	float theta = atan2f(rec_point->y, rec_point->x);

	*/
/*
	if (rec_point->x < 0 && rec_point->y < 0) {	//��l�ی��̎�
		theta = 2 * M_PI + theta;
	}
*/
	//���ꂼ����
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
