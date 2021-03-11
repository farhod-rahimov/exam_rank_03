/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   micro_paint.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <btammara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 08:25:24 by btammara          #+#    #+#             */
/*   Updated: 2021/03/11 09:31:13 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

typedef struct s
{
    int width_b;
    int height_b;
    char c_b;

    char r;
    float x;
    float y;
    float width;
    float height;;
    char c;

    char map[301][301];
} t_struct;
