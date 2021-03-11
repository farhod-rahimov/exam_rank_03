/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_paint.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <btammara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 08:25:26 by btammara          #+#    #+#             */
/*   Updated: 2021/03/11 08:43:00 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <math.h>

typedef struct s
{
    int width_b;
    int height_b;
    char c_b;

    char c;
    float x;
    float y;
    float radius;
    char ch;

    char map[301][301];
}t_struct;
