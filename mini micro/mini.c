/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntadevos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 12:59:46 by ntadevos          #+#    #+#             */
/*   Updated: 2021/04/24 13:36:14 by ntadevos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

typedef struct draw
{
	int w;
	int h;
	char *map;
} draw;

typedef struct cir
{
	char type;
	float x;
	float y;
	float r;
	char color;
} cir;

int init(draw *d, FILE *fp)
{
	char lc;
	if(fscanf(fp, "%d %d %c\n", &d->w, &d->h, &lc) == 3)
	{
		if(d->w <= 0 || d->h <= 0 || d->w > 300 | d->h > 300)
			return 0;
		d->map = malloc(d->w * d->h);
		int i = 0;
		while(i < d->w * d->h)
			d->map[i++] = lc;
		return 1;
	}
	return 0;
}

float dist(float x1, float y1, float x2, float y2)
{
	return(sqrtf((x1 - x2) * (x1-x2) + (y1-y2) *(y1-y2)));
}

int is_in(int x, int y, cir r)
{
	if(dist(x,y, r.x, r.y) - r.r >0.000)
		return 0;
	if(dist(x,y, r.x, r.y) - r.r < -1.0000)
		return 1;
	return 2;
}

int put_map(draw d, cir r)
{
	if(r.r <= 0.0 || (r.type != 'c' && r.type != 'C'))
		return 0;
	int i = 0;
	while(i < d.w)
	{
		int j = 0;
		while(j < d.h)
		{
			if(is_in(i,j,r) == 2 || (is_in(i,j,r) == 1 && r.type == 'C'))
					d.map[j*d.w + i] = r.color;
				j++;
		}
		i++;
	}
	return 1;
}

void print_map(draw d)
{
	int i = 0;
	while(i < d.h)
	{
		write(1, d.map + i*d.w,d.w);
		write(1,"\n",1);
		i++;
	}
}

int execute(FILE *fp)
{
	draw d;
	cir r;
	int ret;
	if(init(&d, fp))
	{
		ret = fscanf(fp, "%c %f %f %f %c\n",&r.type, &r.x, &r.y, &r.r, &r.color);
		while(ret == 5)
		{
			if(!put_map(d,r))
				return 0;
		ret = fscanf(fp, "%c %f %f %f %c\n",&r.type, &r.x, &r.y, &r.r, &r.color);
		}
		if(ret == -1)
		{
			print_map(d);
			return 1;
		}
		return 0;
	}
	return 0;
}


int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		write(1, "er",2);
		return 1;
	}
	FILE *fp = fopen(argv[1], "r");
	if(fp && execute(fp))
		return 0;
	write(1, "ff",1);
	return 1;
}
