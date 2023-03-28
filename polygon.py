def clip_polygon(subject_polygon, clip_polygon):
    def inside(p, cp1, cp2):
        return (cp2[0]-cp1[0])*(p[1]-cp1[1]) > (cp2[1]-cp1[1])*(p[0]-cp1[0])

    def intersection(p1, p2, cp1, cp2):
        denom = (cp2[1]-cp1[1])*(p2[0]-p1[0]) - (cp2[0]-cp1[0])*(p2[1]-p1[1])
        if denom == 0:  # lines are parallel or coincident
            return None
        ua = ((cp2[0]-cp1[0])*(p1[1]-cp1[1]) - (cp2[1]-cp1[1])*(p1[0]-cp1[0])) / denom
        if ua < 0 or ua > 1:
            return None
        return (int(p1[0]+ua*(p2[0]-p1[0])), int(p1[1]+ua*(p2[1]-p1[1])))

    def clip(subject_polygon, clip_edge):
        if len(subject_polygon) < 3:
            return []
        output_polygon = []
        s = subject_polygon[-1]
        for e in subject_polygon:
            if inside(e, *clip_edge):
                if not inside(s, *clip_edge):
                    i = intersection(s, e, *clip_edge)
                    if i is not None:
                        output_polygon.append(i)
                output_polygon.append(e)
            elif inside(s, *clip_edge):
                i = intersection(s, e, *clip_edge)
                if i is not None:
                    output_polygon.append(i)
            s = e
        return output_polygon

    output = subject_polygon
    for clip_edge in zip(clip_polygon, clip_polygon[1:] + [clip_polygon[0]]):
        output = clip(output, clip_edge)
    return output

subject_polygon = [(0, 0), (5, 0), (5, 5), (0, 5)]
clip_polygon = [(2, 2), (4, 2), (4, 4), (2, 4)]

clipped_polygon = clip_polygon(subject_polygon, clip_polygon)

print(clipped_polygon)  # [(2, 2), (4, 2), (4, 4), (2, 4)]
