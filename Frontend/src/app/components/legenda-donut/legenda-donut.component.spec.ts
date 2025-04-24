import { ComponentFixture, TestBed } from '@angular/core/testing';

import { LegendaDonutComponent } from './legenda-donut.component';

describe('LegendaDonutComponent', () => {
  let component: LegendaDonutComponent;
  let fixture: ComponentFixture<LegendaDonutComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      imports: [LegendaDonutComponent]
    })
    .compileComponents();

    fixture = TestBed.createComponent(LegendaDonutComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
