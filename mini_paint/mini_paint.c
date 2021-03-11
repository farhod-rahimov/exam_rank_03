/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_paint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <btammara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 08:29:04 by btammara          #+#    #+#             */
/*   Updated: 2021/03/11 09:15:03 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_paint.h"
int ft_error(char *s, int n);
int ft_parse(FILE *pf);
void ft_fill_back(t_struct *args, int max_y, int max_x);
int ft_print_map(t_struct *args, int max_y, int max_x);
void ft_draw_circle_C(t_struct *args, int max_y, int max_x);
void ft_draw_circle_c(t_struct *args, int max_y, int max_x);
void ft_draw_circle(t_struct *args);

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
    
    if (fscanf(pf, "%d %d %c\n", &args.width_b, &args.height_b, &args.c_b) != 3)
        return (ft_error("Error: Operation file corrupted\n", 32));
    if (args.width_b <= 0 || args.width_b > 300 || args.height_b <= 0 || args.height_b > 300)
        return (ft_error("Error: Operation file corrupted\n", 32));
    ft_fill_back(&args, args.height_b, args.width_b);

    if ((ret = fscanf(pf, "%c %f %f %f %c\n", &args.c, &args.x, &args.y, &args.radius, &args.ch)) != -1 && ret != 5)
        return (ft_error("Error: Operation file corrupted\n", 32));
    if (ret == -1)
        return (ft_print_map(&args, args.height_b, args.width_b));
    if (ret == 5)
        if ((args.c != 'c' && args.c != 'C') || args.radius <= 0)
            return (ft_error("Error: Operation file corrupted\n", 32));
    ft_draw_circle(&args);
    
    while (ret)
    {
        if ((ret = fscanf(pf, "%c %f %f %f %c\n", &args.c, &args.x, &args.y, &args.radius, &args.ch)) != -1 && ret != 5)
            return (ft_error("Error: Operation file corrupted\n", 32));
        if (ret == -1)
            break ;
        if (ret == 5)
            if ((args.c != 'c' && args.c != 'C') || args.radius <= 0)
                return (ft_error("Error: Operation file corrupted\n", 32));
        ft_draw_circle(&args);
    }
    return (ft_print_map(&args, args.height_b, args.width_b)); 
}

void ft_draw_circle(t_struct *args)
{
    if (args->c == 'C')
        ft_draw_circle_C(args, args->height_b, args->width_b);
    else
        ft_draw_circle_c(args, args->height_b, args->width_b);
}

void ft_draw_circle_C(t_struct *args, int max_y, int max_x)
{
    int y;
    int x;
    float tmp;

    y = (int)(args->y - args->radius);
    x = (int)(args->x - args->radius);

    while (y <= args->y + args->radius && y < max_y)
    {
        while (x <= args->x + args->radius && x < max_x)
        {
            if (x >= 0 && y >= 0)
                if ((tmp = sqrtf((args->x - x) * (args->x - x) + (args->y - y) * (args->y - y))) <= args->radius)
                    args->map[y][x] = args->ch;
            x++;
        }
        x = (int)(args->x - args->radius);
        y++;
    }
}

void ft_draw_circle_c(t_struct *args, int max_y, int max_x)
{
    int y;
    int x;
    float tmp;

    y = (int)(args->y - args->radius);
    x = (int)(args->x - args->radius);

    while (y <= args->y + args->radius && y < max_y)
    {
        while (x <= args->x + args->radius && x < max_x)
        {
            if (x >= 0 && y >= 0)
                if ((tmp = sqrtf((args->x - x) * (args->x - x) + (args->y - y) * (args->y - y))) <= args->radius)
                    if (args->radius - tmp < 1)
                        args->map[y][x] = args->ch;
            x++;
        }
        x = (int)(args->x - args->radius);
        y++;
    }
    
}

int ft_print_map(t_struct *args, int max_y, int max_x)
{
    int y;

    y = 0;
    while (y < max_y)
    {
        write(1, args->map[y++], max_x);
        write(1, "\n", 1);
    }
    return (0);
}

void ft_fill_back(t_struct *args, int max_y, int max_x)
{
    int x;
    int y;

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