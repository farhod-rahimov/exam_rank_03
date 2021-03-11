/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   micro_paint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <btammara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 08:25:24 by btammara          #+#    #+#             */
/*   Updated: 2021/03/11 10:05:37 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "micro_paint.h"
int ft_error(char *s, int n);
void ft_fill_back(t_struct *args, int max_y, int max_x);
int ft_print_map(t_struct *args, int max_y, int max_x);
void ft_draw_rec(t_struct *args, int max_y, int max_x);
void ft_draw_rec_r(t_struct *args, int max_y, int max_x);
void ft_draw_rec_R(t_struct *args, int max_y, int max_x);
int ft_parse(FILE *pf);

int main(int argc, char **argv)
{
    FILE *pf;
    
    if (argc != 2)
        return (ft_error("Error: argument\n", 16));
    if ((pf = fopen(argv[1], "r")) == NULL)
        return (ft_error("Error: Operation file corrupted\n", 32));
    return (ft_parse(pf));
}

int ft_parse(FILE *pf)
{
    t_struct args;
    int ret;

    if ((fscanf(pf, "%d %d %c\n", &args.width_b, &args.height_b, &args.c_b)) != 3)
        return (ft_error("Error: Operation file corrupted\n", 32));
    if (args.width_b <= 0 || args.width_b > 300 || args.height_b <= 0 || args.height_b > 300)
        return (ft_error("Error: Operation file corrupted\n", 32));
    
    ft_fill_back(&args, args.height_b, args.width_b);
    
    if ((ret = fscanf(pf, "%c %f %f %f %f %c\n", &args.r, &args.x, &args.y, &args.width, &args.height, &args.c)) != -1 && ret != 6)
        return (ft_error("Error: Operation file corrupted\n", 32));
    if (ret == -1)
        return (ft_print_map(&args, args.height_b, args.width_b));
    if (ret == 6)
        if ((args.r != 'R' && args.r != 'r') || args.width <= 0 || args.height <= 0)
            return (ft_error("Error: Operation file corrupted\n", 32));
    ft_draw_rec(&args, args.height_b, args.width_b);

    while (ret)
    {
        if ((ret = fscanf(pf, "%c %f %f %f %f %c\n", &args.r, &args.x, &args.y, &args.width, &args.height, &args.c)) != -1 && ret != 6)
            return (ft_error("Error: Operation file corrupted\n", 32));
        if (ret == -1)
            break ;
        if (ret == 6)
            if ((args.r != 'R' && args.r != 'r') || args.width <= 0 || args.height <= 0)
                return (ft_error("Error: Operation file corrupted\n", 32));
        ft_draw_rec(&args, args.height_b, args.width_b);
    }
    return (ft_print_map(&args, args.height_b, args.width_b));
}

void ft_draw_rec(t_struct *args, int max_y, int max_x)
{
    if (args->r == 'R')
        ft_draw_rec_R(args, max_y, max_x);
    else
        ft_draw_rec_r(args, max_y, max_x);
}

void ft_draw_rec_R(t_struct *args, int max_y, int max_x)
{
    int y;
    int x;
    
    y = (int)args->y;
    x = (int)args->x;
    while (y <= args->y + args->height && y < max_y)
    {
        while (x <= args->x + args->width && x < max_x)
        {
            if (y >= 0 && x >= 0)
            {
                if (y >= args->y && y <= args->y + args->height && x >= args->x && x <= args->x + args->width)
                    args->map[y][x] = args->c;    
            }
            x++;
        }
        x = (int)args->x;
        y++;
    }    
}

void ft_draw_rec_r(t_struct *args, int max_y, int max_x)
{
    int y;
    int x;
    float tmp_y;
    float tmp_x;
    
    y = (int)args->y;
    x = (int)args->x;
    while (y <= args->y + args->height && y < max_y)
    {
        while (x <= args->x + args->width && x < max_x)
        {
            if (y >= 0 && x >= 0)
            {
                if (y >= args->y && y <= args->y + args->height && x >= args->x && x <= args->x + args->width)
                {
                    if (((tmp_y = y - args->y) < 1 && tmp_y >= 0) || ((tmp_x = x - args->x) < 1 && tmp_x >= 0))
                        args->map[y][x] = args->c;
                    if (((tmp_y = args->y + args->height - y) < 1 && tmp_y >= 0) || ((tmp_x = args->x + args->width - x) < 1 && tmp_x >= 0))
                        args->map[y][x] = args->c;
                }
            }
            x++;
        }
        x = (int)args->x;
        y++;
    }    
}

int ft_print_map(t_struct *args, int max_y, int max_x)
{
    int y;

    y = 0;
    while (y < max_y)
    {
        write (1, args->map[y++], max_x);
        write (1, "\n", 1);
    }
    return (0);
}

void ft_fill_back(t_struct *args, int max_y, int max_x)
{
    int y;
    int x;

    y = 0;
    x = 0;
    while (y < max_y)
    {
        while (x < max_x)
            args->map[y][x++] = args->c_b;
        x = 0;
        y++;
    }    
}

int ft_error(char *s, int n)
{
    write(1, s, n);
    return (1);
}