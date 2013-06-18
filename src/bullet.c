#include "speedoman.h"

void bulletLoadTypes() {
	DARNIT_FILE *f;
	int i, num[7];
	char buff[2048];

	f = d_file_open("assets/bullets.lst", "rb");
	s->bullet.type = NULL;
	s->bullet.types = 0;

	for (i = 0; !d_file_eof(f); i++) {
		s->bullet.type = realloc(s->bullet.type, (i + 1) * sizeof(BULLET_TYPE));
		d_file_gets(buff, 2048, f);
		if (!strlen(buff))
			break;
		d_util_string_to_int_array(buff, " ", num, 7);
		s->bullet.type[i].x_pos = num[0];
		s->bullet.type[i].y_pos = num[1];
		s->bullet.type[i].w = num[2];
		s->bullet.type[i].h = num[3];
		s->bullet.type[i].x_speed = num[4];
		s->bullet.type[i].y_speed = num[5];
		s->bullet.type[i].life = num[6];
	}

	s->bullet.types = i;
	d_file_close(f);

	f = d_file_open("assets/bullets.dmg", "rb");
	s->bullet.dmg = malloc(sizeof(int) * i * i);
	for (i = 0; i < s->bullet.types; i++) {
		d_file_gets(buff, 2048, f);
		d_util_string_to_int_array(buff, " ", s->bullet.dmg, s->bullet.types);
	}

	d_file_close(f);

	return;
}


void bulletUnloadTypes() {
	free(s->bullet.type);
	s->bullet.types = 0;

	return;
}


void bulletInit() {
	s->bullet.b = malloc(sizeof(BULLET_ENTRY) * BULLET_CAP);
	memset(s->bullet.b, 0, sizeof(BULLET_ENTRY) * BULLET_CAP);
	s->bullet.bs = BULLET_CAP;
	s->bullet.ts = d_render_tilesheet_load("assets/bullets.png", 32, 32, DARNIT_PFORMAT_RGB5A1);
	s->bullet.tc = d_render_tile_new(BULLET_CAP, s->bullet.ts);
	s->bullet.bbox = d_bbox_new(BULLET_CAP);
	s->bullet.btest = malloc(sizeof(int) * BULLET_CAP);
	bulletLoadTypes();
	
	return;
}


void bulletDelete(int i) {
	d_bbox_delete(s->bullet.bbox, i);
	d_render_tile_move(s->bullet.tc, i, INT_MAX, INT_MAX);
	s->bullet.b[i].x = INT_MAX;
	s->bullet.b[i].y = INT_MAX;

	return;
}


void bulletLoop() {
	int i, dx;

	for (i = 0; i < BULLET_CAP; i++) {
		if (s->bullet.b[i].life <= 0)
			continue;
		dx = s->bullet.b[i].x_vel * d_last_frame_time();
		s->bullet.b[i].life -= d_last_frame_time();
		if (s->bullet.b[i].life <= 0) {
			bulletDelete(i);
			dx = 0;
		} else {
			s->bullet.b[i].x += dx;
			d_render_tile_move(s->bullet.tc, i, s->bullet.b[i].x / 1000, s->bullet.b[i].y / 1000);
			d_bbox_move(s->bullet.bbox, i, (s->bullet.b[i].x) / 1000, s->bullet.b[i].y / 1000);
			d_bbox_resize(s->bullet.bbox, i, abs(dx/1000) + s->bullet.type[s->bullet.b[i].type].w, s->bullet.type[s->bullet.b[i].type].h);
		}

		d_render_tile_size_set(s->bullet.tc, i, s->bullet.type[s->bullet.b[i].type].w, s->bullet.type[s->bullet.b[i].type].h);
	}

	return;
}


void bulletDraw() {
	d_render_tile_draw(s->bullet.tc, ~0);

	return;
}


void bulletSpawn(int type, int direction, MOVABLE_ENTRY *owner_e, int x, int y) {
	int key, owner;
	
	owner = (int) (owner_e - s->movable.movable);
	owner /= sizeof(MOVABLE_ENTRY);

	if (direction < 0)
		x -= s->bullet.type[type].w;

	if ((key = d_bbox_add(s->bullet.bbox, x, y, s->bullet.type[type].w, s->bullet.type[type].h)) < 0)
		return;
	s->bullet.b[key].x = x * 1000;
	s->bullet.b[key].y = y * 1000;
	s->bullet.b[key].x_vel = s->bullet.type[type].x_speed * direction;
	s->bullet.b[key].y_vel = s->bullet.type[type].y_speed;
	s->bullet.b[key].owner = owner;
	s->bullet.b[key].life = s->bullet.type[type].life; 
	s->bullet.b[key].type = type;
	d_render_tile_tilesheet_coord_set(s->bullet.tc, key, s->bullet.type[type].x_pos, s->bullet.type[type].y_pos, s->bullet.type[type].w, s->bullet.type[type].h);

	return;
}


void bulletOrphan(int owner) {
	int i;

	for (i = 0; i < BULLET_CAP; i++)
		if (s->bullet.b[i].owner == owner)
			s->bullet.b[i].owner = -1;

	return;
}


void bulletTest(MOVABLE_ENTRY *entry) {
	int box_x, box_y, box_w, box_h, i, res, hit;

	d_sprite_hitbox(entry->sprite, &box_x, &box_y, &box_w, &box_h);
	box_x += (entry->x / 1000);
	box_y += (entry->y / 1000);

	res = d_bbox_test(s->bullet.bbox, box_x, box_y, box_w, box_h, s->bullet.btest, BULLET_CAP);

	for (i = 0, hit = -1; i < res; i++) {
		if (&s->movable.movable[s->bullet.b[s->bullet.btest[i]].owner] == entry)
			continue;
		hit = s->bullet.b[s->bullet.btest[i]].type;
		bulletDelete(s->bullet.btest[i]);
	}

	if (!entry->hit && hit > -1) {
		fprintf(stderr, "Had %i hp, subtracting %i (%i)\n", entry->hp, s->bullet.dmg[s->bullet.types * entry->type + hit], s->bullet.types * entry->type + hit);
		entry->hp -= s->bullet.dmg[s->bullet.types * entry->type + hit];
		entry->hit = 1;
		/* TODO: Insert sound effect playback thing */
	}

	return;
}


void bulletDeInit() {
	free(s->bullet.b);
	s->bullet.bs = 0;
	s->bullet.tc = d_render_tile_free(s->bullet.tc);
	s->bullet.ts = d_render_tilesheet_free(s->bullet.ts);
	s->bullet.bbox = d_bbox_free(s->bullet.bbox);
	bulletUnloadTypes();
	free(s->bullet.btest);

	return;
}
