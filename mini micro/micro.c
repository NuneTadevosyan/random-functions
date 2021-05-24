/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   micro.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntadevos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 13:36:38 by ntadevos          #+#    #+#             */
/*   Updated: 2021/04/24 14:17:22 by ntadevos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

typedef struct draw
{
	int w;
	int h;
	char *map;
}	draw;

typedef struct rect
{
	char type;
	float x;
	float y;
	float w;
	float h;
	char color;
} rect;

int init(draw *d, FILE *fp)
{
	char lc;
	if(fscanf(fp,"%d %d %c\n", &d->w, &d->h, &lc) == 3)
	{
		if(d->w > 300 || d->h > 300 || d->w <= 0 || d->h <= 0)
			return 0;
		d->map = malloc(d->w *d->h);
		int i = 0;
		while(i < d->w * d->h)
			d->map[i++] = lc;
		return 1;
	}
	return 0;
}

int is_in(int x, int y, rect r)
{
	if(x<r.x || y < r.h || x > r.x + r.w || y > r.h + r.y)
			return 0;
	if((x - r.x) < 1.0000 || (r.x + r.w - x) < 1.0000 || (y - r.y) < 1.0000 || (r.y + r.h - y) < 1.00000)
		return 2;
	return 1;
}

int put_map(draw d, rect r)
{
	if(r.w < 0.0 || r.h < 0.0 || (r.type != 'r' && r.type != 'R'))
		return 0;
	int i = 0;
	while(i < d.w)
	{
		int j = 0;
		while(j < d.h)
		{
			if(is_in(i,j,r) == 1 || ( is_in(i,j,r) == 2 && r.type == 'C'))
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
		write(1, d.map + i*d.w, d.w);
		write(1,"\n",1);
		i++;
	}
}

int execute(FILE *fp)
{
	draw d;
	rect r;
	int ret;
	if(init(&d, fp))
	{
		ret = fscanf(fp, "%c %f %f %f %f %c\n", &r.type, &r.x, &r.y, &r.w, &r.h,&r.color);
		while(ret == 6)
		{
			if(!put_map(d,r))
				return 0;
			ret = fscanf(fp, "%c %f %f %f %f %c\n", &r.type, &r.x, &r.y, &r.w, &r.h,&r.color);
		}
		if(ret == -1)
		{
			print_map(d);
			return 1;
		}
		return 0;
	}
	return (0);
}

int main (int argc, char *argv[])
{
	if(argc != 2)
	{
		write(1,"eee",1);
		return 1;
	}
	FILE *fp = fopen(argv[1], "r");
	if(fp && execute(fp))
		return 0;
	write(1,"r",1);
	return 0;
}



