package dainosaur.dinosaurserver.dto;

import dainosaur.dinosaurserver.entity.Score;

public record ScoreDto(
        Integer score
){
    public static ScoreDto fromEntity(Score score){
        return new ScoreDto(score.getScore());
    }

    public Score toEntity(){
        return Score.builder()
                .score(score)
                .build();
    }
}
